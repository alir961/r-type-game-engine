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
#include <Windows.h>

namespace RType {

    enum class ModuleType {
        SOUND, CONSOLE, PARTICLE, GRAPHICAL, UNKNOWN, ANIMATION
    };

    template<typename T>
    class ModuleLoader {
    public:
        explicit ModuleLoader(const std::string &path);
        ModuleLoader(ModuleLoader &&_instance) noexcept = delete;
        ModuleLoader(ModuleLoader &_instance) = delete;
        ~ModuleLoader();

        T *load();
        void unload();

        static ModuleType getModuleType(const std::string &path, void *existingHandle = nullptr);

    private:
        T *callConstructor(const std::string &functionName) const;

        HMODULE _handle = nullptr;
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

        initializeModule = reinterpret_cast<T *(*)()>(GetProcAddress(_handle, functionName.c_str()));

        if (initializeModule != nullptr)
            return initializeModule();
        throw ModuleException("Invalid library provided");
    }

    template<typename T>
    ModuleLoader<T>::ModuleLoader(const std::string &path) {
        _handle = LoadLibrary(path.c_str());

        if (_handle == nullptr) {
            DWORD errorMessageID = GetLastError();
            LPVOID errorMessageBuffer;
            FormatMessageW(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                    nullptr,
                    errorMessageID,
                    0,
                    reinterpret_cast<LPWSTR>(&errorMessageBuffer),
                    0,
                    nullptr
            );

            wchar_t* wideErrorMessage = reinterpret_cast<wchar_t*>(errorMessageBuffer);
            int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideErrorMessage, -1, nullptr, 0, nullptr, nullptr);
            std::string errorMessage(bufferSize, 0);
            WideCharToMultiByte(CP_UTF8, 0, wideErrorMessage, -1, errorMessage.data(), bufferSize, nullptr, nullptr);

            LocalFree(errorMessageBuffer);

            throw ModuleException("Module '" + path + "' cannot be loaded: " + errorMessage);
        }
        _type = getModuleType(path, _handle);
    }

    template<typename T>
    T *ModuleLoader<T>::load() {
        T *loadedModule = nullptr;
        if (_module != nullptr) return _module;

        if (_type == ModuleType::SOUND)
            loadedModule = callConstructor("initializeSoundModule");
        if (_type == ModuleType::CONSOLE)
            loadedModule = callConstructor("initializeConsoleModule");
        if (_type == ModuleType::PARTICLE)
            loadedModule = callConstructor("initializeParticleModule");
        if (_type == ModuleType::GRAPHICAL)
            loadedModule = callConstructor("initializeGraphicalModule");
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
        destroyLibrary = reinterpret_cast<void (*)(T *)>(GetProcAddress(_handle, "destroy"));
        if (destroyLibrary != nullptr)
            destroyLibrary(_module);
        _module = nullptr;
    }

    template<typename T>
    ModuleLoader<T>::~ModuleLoader() {
        if (_handle != nullptr)
            FreeLibrary(_handle);
    }

    template<typename T>
    ModuleType ModuleLoader<T>::getModuleType(const std::string &path, void *existingHandle) {
        HMODULE handle = (existingHandle == nullptr ? LoadLibrary(path.c_str()) : reinterpret_cast<HMODULE>(existingHandle));

        if (handle == nullptr)
            return ModuleType::UNKNOWN;

        if (GetProcAddress(handle, "initializeSoundModule") != nullptr)
            return ModuleType::SOUND;

        if (GetProcAddress(handle, "initializeConsoleModule") != nullptr)
            return ModuleType::CONSOLE;

        if (GetProcAddress(handle, "initializeParticleModule") != nullptr)
            return ModuleType::PARTICLE;

        if (GetProcAddress(handle, "initializeGraphicalModule") != nullptr)
            return ModuleType::GRAPHICAL;

        return ModuleType::UNKNOWN;
    }

}
#else
#include <dlfcn.h>

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

        *(void **) (&initializeModule) = dlsym(_handle, functionName.c_str());

        if (initializeModule != nullptr)
            return initializeModule();
        throw ModuleException("Invalid library provided");
    }

    template<typename T>
    ModuleLoader<T>::ModuleLoader(const std::string &path) {
        if (_handle != nullptr)
            dlclose(_handle);
        _handle = dlopen(path.c_str(), RTLD_LAZY);

        if (_handle == nullptr) {
            const std::string errorMessage = dlerror();

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
        *(void **) (&destroyLibrary) = dlsym(_handle, "destroy");
        destroyLibrary(_module);
        _module = nullptr;
    }

    template<typename T>
    ModuleLoader<T>::~ModuleLoader() {
        if (_handle != nullptr)
            dlclose(_handle);
    }

    template<typename T>
    ModuleType ModuleLoader<T>::getModuleType(const std::string &path, void *existingHandle) {
        void *handle = (existingHandle == nullptr ? dlopen(path.c_str(), RTLD_LAZY) : existingHandle);

        if (handle == nullptr)
            return ModuleType::UNKNOWN;
        if (dlsym(handle, "initializeSoundModule") != nullptr)
            return ModuleType::SOUND;
        if (dlsym(handle, "initializeConsoleModule") != nullptr)
            return ModuleType::CONSOLE;
        if (dlsym(handle, "initializeParticleModule") != nullptr)
            return ModuleType::PARTICLE;
        if (dlsym(handle, "initializeGraphicalModule") != nullptr)
            return ModuleType::GRAPHICAL;
        if (dlsym(handle, "initializeAnimationModule") != nullptr)
            return ModuleType::ANIMATION;
        if (dlsym(handle, "initializeLoggerModule") != nullptr)
            return ModuleType::LOGGER;
        return ModuleType::UNKNOWN;
    }

}
#endif