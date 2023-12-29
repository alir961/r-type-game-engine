/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <string>
#include <dlfcn.h>
#include "engine/exception/ModuleException.hpp"

namespace RType {

    enum class ModuleType {
        SOUND, UNKNOWN
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

        if (_type == ModuleType::SOUND)
            loadedModule = callConstructor("initializeSoundModule");
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
        return ModuleType::UNKNOWN;
    }

}
