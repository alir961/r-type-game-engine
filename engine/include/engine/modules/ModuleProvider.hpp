/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <memory>
#include <map>
#include <iostream>
#include "ModuleLoader.hpp"
#include "IModule.hpp"
#include "engine/modules/logger/ILoggerModule.hpp"

namespace RType {

    template<typename T>
    using ModuleLoaderPtr = std::shared_ptr<ModuleLoader<T>>;

#ifdef _WIN32
#define RTYPE_MODULE_SUFFIX ".dll"
#else
#define RTYPE_MODULE_SUFFIX ".so"
#endif

    /**
     * @brief Paths of the engine modules, relative to the repository root (see rtype_module in CMakeLists.txt).
     */
    constexpr std::string_view MODULE_ANIMATION_PATH = "build/out/engine/modules/animation/libanimation_module" RTYPE_MODULE_SUFFIX;
    constexpr std::string_view MODULE_GRAPHICAL_PATH = "build/out/engine/modules/graphical/libgraphical_module" RTYPE_MODULE_SUFFIX;
    constexpr std::string_view MODULE_SOUND_PATH = "build/out/engine/modules/sound/libsound_module" RTYPE_MODULE_SUFFIX;
    constexpr std::string_view MODULE_PARTICLE_PATH = "build/out/engine/modules/particle/libparticle_module" RTYPE_MODULE_SUFFIX;
    constexpr std::string_view MODULE_CONSOLE_PATH = "build/out/engine/modules/console/libconsole_module" RTYPE_MODULE_SUFFIX;
    constexpr std::string_view MODULE_LOGGER_PATH = "build/out/engine/modules/logger/liblogger_module" RTYPE_MODULE_SUFFIX;

    class ModuleProvider;

    using ModuleProviderPtr = std::shared_ptr<ModuleProvider>;

    /**
     * @brief Class representing a module provider that manages loading and unloading of modules.
     */
    class ModuleProvider {
    private:
        std::map<ModuleType, ModuleLoaderPtr<IModule>> _loaders;
        std::map<ModuleType, IModule *> _modules;
        ILoggerModule *_logger = nullptr;

        static std::string retrieveModuleName(ModuleType type);

    public:
        /**
         * @brief Explicit constructor to initialize the ModuleProvider.
         */
        explicit ModuleProvider();

        /**
         * @brief Destructor to unload all loaded modules and release resources.
         */
        ~ModuleProvider();

        /**
         * @brief Loads the module of the specified type.
         * @param type The type of the module to load.
         */
        void loadModule(ModuleType type);

        /**
         * @brief Unloads the module of the specified type.
         * @param type The type of the module to unload.
         */
        void unloadModule(ModuleType type);

        template<typename T>
        T *loadAndGetModule(ModuleType type) {
            if (!_modules.contains(type))
                loadModule(type);
            IModule *moduleInstance = _modules[type];

            return dynamic_cast<T *>(moduleInstance);
        }

        /**
         * @brief Gets a pointer to the module of the specified type.
         * @tparam T The type of the module.
         * @param type The type of the module to get.
         * @return A pointer to the module, or nullptr if not found.
         */
        template<typename T>
        [[nodiscard]] T *get(ModuleType type) {
            if (!_modules.contains(type))
                return nullptr;
            IModule *moduleInstance = _modules[type];

            return dynamic_cast<T *>(moduleInstance);
        }

        static ModuleProviderPtr getInstance() {
            static ModuleProviderPtr instance = nullptr;

            if (instance == nullptr)
                instance = std::make_shared<ModuleProvider>();
            return instance;
        }
    };

}