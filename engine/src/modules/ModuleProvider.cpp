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
}

void RType::ModuleProvider::unloadModule(RType::ModuleType type) {
    if (!_modules.contains(type))
        return;
    _modules[type]->unload();
    _loaders[type]->unload();
    _modules.erase(type);
}
