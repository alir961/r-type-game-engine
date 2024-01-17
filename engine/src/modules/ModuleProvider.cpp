/*/home/joan/delivery/rtype/client/include/ClientViewport.hpp:68:9:
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "engine/modules/ModuleProvider.hpp"

RType::ModuleProvider::ModuleProvider() {
    const auto initLoader = [](const std::string_view &path) {
        return std::make_shared<ModuleLoader<IModule>>(std::string(path));
    };

    _loaders.emplace(ModuleType::ANIMATION, initLoader(MODULE_ANIMATION_PATH));
    _loaders.emplace(ModuleType::GRAPHICAL, initLoader(MODULE_GRAPHICAL_PATH));
    _loaders.emplace(ModuleType::SOUND, initLoader(MODULE_SOUND_PATH));
    _loaders.emplace(ModuleType::PARTICLE, initLoader(MODULE_PARTICLE_PATH));
    _loaders.emplace(ModuleType::CONSOLE, initLoader(MODULE_CONSOLE_PATH));
    _loaders.emplace(ModuleType::LOGGER, initLoader(MODULE_LOGGER_PATH));
    _logger = loadAndGetModule<ILoggerModule>(ModuleType::LOGGER);
}

RType::ModuleProvider::~ModuleProvider() {
    try {
        for (const auto &[type, module]: _modules)
            unloadModule(type);
    } catch (const ModuleException &exception ) {
        std::cerr << "Unable to unload module:" << exception.what() << "\n";
    }
}

void RType::ModuleProvider::loadModule(RType::ModuleType type) {
    if (_modules.contains(type))
        return;
    _modules.emplace(type, _loaders[type]->load());
    _modules[type]->load();
    if (type == ModuleType::LOGGER)
        _logger = get<ILoggerModule>(ModuleType::LOGGER);
    if (_logger != nullptr)
        _logger->info("Load module " + retrieveModuleName(type));
}

void RType::ModuleProvider::unloadModule(RType::ModuleType type) {
    if (!_modules.contains(type))
        return;
    _modules[type]->unload();
    _loaders[type]->unload();
    _modules.erase(type);
    if (type == ModuleType::LOGGER)
        _logger = nullptr;
    if (_logger != nullptr)
        _logger->info("Unload module " + retrieveModuleName(type));
}

std::string RType::ModuleProvider::retrieveModuleName(RType::ModuleType type) {
    switch (type) {
        case ModuleType::ANIMATION:
            return "Animation";
        case ModuleType::SOUND:
            return "Sound";
        case ModuleType::CONSOLE:
            return "Console";
        case ModuleType::PARTICLE:
            return "Particle";
        case ModuleType::GRAPHICAL:
            return "Graphical";
        case ModuleType::LOGGER:
            return "Logger";
        default:
            return "Unknown";
    }
}


