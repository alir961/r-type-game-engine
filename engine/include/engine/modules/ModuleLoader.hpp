/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "engine/exception/ModuleException.hpp"
#include <string>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace RType::detail {

    // Thin wrappers over the platform's shared-library API, so ModuleLoader has a single implementation.
#ifdef _WIN32
    inline void *openLibrary(const std::string &path) { return reinterpret_cast<void *>(LoadLibraryA(path.c_str())); }
    inline void *findSymbol(void *handle, const char *name) {
        return reinterpret_cast<void *>(GetProcAddress(static_cast<HMODULE>(handle), name));
    }
    inline void closeLibrary(void *handle) { FreeLibrary(static_cast<HMODULE>(handle)); }
    inline std::string lastLibraryError() {
        char *buffer = nullptr;
        const DWORD size = FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr,
            GetLastError(), 0, reinterpret_cast<LPSTR>(&buffer), 0, nullptr);
        std::string message = size ? std::string(buffer, size) : "unknown error";
        LocalFree(buffer);
        return message;
    }
#else
    inline void *openLibrary(const std::string &path) { return dlopen(path.c_str(), RTLD_LAZY); }
    inline void *findSymbol(void *handle, const char *name) { return dlsym(handle, name); }
    inline void closeLibrary(void *handle) { dlclose(handle); }
    inline std::string lastLibraryError() {
        const char *error = dlerror();
        return error ? error : "unknown error";
    }
#endif

}

namespace RType {

    enum class ModuleType {
        ANIMATION, SOUND, CONSOLE, PARTICLE, GRAPHICAL, LOGGER, UNKNOWN
    };

    /**
     * @brief Template class for dynamically loading and managing modules.
     * @tparam T The type of the module to be loaded.
     */
    template<typename T>
    class ModuleLoader {
    public:
        /**
        * @brief Explicit constructor to initialize the ModuleLoader with the specified path.
        * @param path The path to the module file.
        */
        explicit ModuleLoader(const std::string &path);
        ModuleLoader(ModuleLoader &&instance) noexcept = delete;
        ModuleLoader(ModuleLoader &instance) = delete;

        /**
         * @brief Destructor to unload the module and release resources.
         */
        ~ModuleLoader();

        /**
         * @brief Loads the module and returns a pointer to the instantiated object of type T.
         * @return A pointer to the loaded module object.
         */
        T *load();

        /**
         * @brief Unloads the module.
         */
        void unload();

        /**
         * @brief Static method to get the module type based on the provided path.
         * @param path The path to the module file.
         * @param existingHandle Pointer to an existing module handle (optional).
         * @return The module type determined based on the path.
         */
        static ModuleType getModuleType(const std::string &path, void *existingHandle = nullptr);

    private:
        /**
         * @brief Calls the constructor function with the specified name in the loaded module.
         * @param functionName The name of the constructor function.
         * @return A pointer to the instantiated object of type T.
         */
        [[nodiscard]] T *callConstructor(const std::string &functionName) const;

        void *_handle = nullptr;
        T *_module = nullptr;
        ModuleType _type = ModuleType::UNKNOWN;
    };

    template<typename T>
    T *ModuleLoader<T>::callConstructor(const std::string &functionName) const {
        T *(*initializeModule)() = nullptr;

        if (_handle == nullptr)
            throw ModuleException("No module loaded");
        if (_type == ModuleType::UNKNOWN)
            throw ModuleException("Invalid module provided");

        initializeModule = reinterpret_cast<T *(*)()>(detail::findSymbol(_handle, functionName.c_str()));

        if (initializeModule != nullptr)
            return initializeModule();
        throw ModuleException("Invalid library provided");
    }

    template<typename T>
    ModuleLoader<T>::ModuleLoader(const std::string &path) {
        _handle = detail::openLibrary(path);

        if (_handle == nullptr) {
            const std::string errorMessage = detail::lastLibraryError();

            throw ModuleException("Module '" + path + "' cannot be load: " + errorMessage);
        }
        _type = getModuleType(path, _handle);
    }

    template<typename T>
    T *ModuleLoader<T>::load() {
        T *loadedModule = nullptr;
        if (_module != nullptr) return _module;
        if (_type == ModuleType::ANIMATION)
            loadedModule = callConstructor("initializeAnimationModule");
        if (_type == ModuleType::SOUND)
            loadedModule = callConstructor("initializeSoundModule");
        if (_type == ModuleType::CONSOLE)
            loadedModule = callConstructor("initializeConsoleModule");
        if (_type == ModuleType::PARTICLE)
            loadedModule = callConstructor("initializeParticleModule");
        if (_type == ModuleType::GRAPHICAL)
            loadedModule = callConstructor("initializeGraphicalModule");
        if (_type == ModuleType::LOGGER)
            loadedModule = callConstructor("initializeLoggerModule");
        if (loadedModule == nullptr)
            throw ModuleException("Invalid loadedModule provided");
        _module = loadedModule;
        return loadedModule;
    }

    template<typename T>
    void ModuleLoader<T>::unload() {
        void (*destroyLibrary)(T *) = nullptr;

        if (_module == nullptr) return;
        if (_handle == nullptr) throw ModuleException("No library loaded");
        destroyLibrary = reinterpret_cast<void (*)(T *)>(detail::findSymbol(_handle, "destroy"));
        if (destroyLibrary != nullptr)
            destroyLibrary(_module);
        _module = nullptr;
    }

    template<typename T>
    ModuleLoader<T>::~ModuleLoader() {
        if (_handle != nullptr)
            detail::closeLibrary(_handle);
    }

    template<typename T>
    ModuleType ModuleLoader<T>::getModuleType(const std::string &path, void *existingHandle) {
        void *handle = (existingHandle == nullptr ? detail::openLibrary(path) : existingHandle);

        if (handle == nullptr)
            return ModuleType::UNKNOWN;
        if (detail::findSymbol(handle, "initializeSoundModule") != nullptr)
            return ModuleType::SOUND;
        if (detail::findSymbol(handle, "initializeConsoleModule") != nullptr)
            return ModuleType::CONSOLE;
        if (detail::findSymbol(handle, "initializeParticleModule") != nullptr)
            return ModuleType::PARTICLE;
        if (detail::findSymbol(handle, "initializeGraphicalModule") != nullptr)
            return ModuleType::GRAPHICAL;
        if (detail::findSymbol(handle, "initializeAnimationModule") != nullptr)
            return ModuleType::ANIMATION;
        if (detail::findSymbol(handle, "initializeLoggerModule") != nullptr)
            return ModuleType::LOGGER;
        return ModuleType::UNKNOWN;
    }

}
