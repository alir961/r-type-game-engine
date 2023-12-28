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

    struct Module {
        ModuleType type;
        std::string path;
        std::string name;
    };

    template<typename T>
    class ModuleLoader {
    public:
        explicit ModuleLoader(const std::string &path);
        ModuleLoader(ModuleLoader &&instance) noexcept = delete;
        ModuleLoader(ModuleLoader &instance) = delete;

        T *load();
        void unload();

        ~ModuleLoader();

        static ModuleType getModuleType(const std::string &path, void *existingHandle = nullptr);

    private:
        [[nodiscard]] T *callConstructor(const std::string &functionName) const;

        void *_handle = nullptr;
        T *_module = nullptr;
        ModuleType _type = ModuleType::UNKNOWN;
    };

    template<typename T>
    T *ModuleLoader<T>::callConstructor(const std::string &functionName) const {
        T *(*initializeModule)();

        if (_handle == nullptr)
            throw ModuleException("No module loaded");
        if (_type == ModuleType::UNKNOWN)
            throw ModuleException("Invalid module provided");

        *(void **) (&initializeModule) = dlsym(_handle, functionName.c_str());

        std::cout << "call constructor\n";
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
        void (*destroyLibrary)(T *);

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
