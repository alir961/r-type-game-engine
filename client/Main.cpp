#include <engine/Logger.hpp>
#include <engine/network/UDPAdapter.hpp>
#include "include/GameView.hpp"
#include "engine/network/NetworkMessage.hpp"
#include "engine/modules/ModuleLoader.hpp"
#include "../engine/modules/sound/SoundModule.hpp"
#include "../engine/modules/console/ConsoleModule.hpp"
#include "../engine/modules/particle/ParticleModule.hpp"
#include "../engine/modules/graphical/GraphicalModule.hpp"

int main() {
    asio::io_context ioContext;
    const asio::ip::address &serverAddress = asio::ip::address::from_string("127.0.0.1");
    const UDP::endpoint endpoint(serverAddress, 9002);
    RType::ModuleLoader<RType::SoundModule> soundModuleLoader("build/out/engine/modules/sound/libsound_module.so");
    RType::ModuleLoader<RType::ConsoleModule> consoleModuleLoader("build/out/engine/modules/console/libconsole_module.so");
    RType::ModuleLoader<RType::ParticleModule> particleModuleLoader("build/out/engine/modules/particle/libparticle_module.so");
    RType::ModuleLoader<RType::IGraphicalModule> graphicalModuleLoader("build/out/engine/modules/graphical/libgraphical_module.so");
    RType::SoundModule *soundModule = soundModuleLoader.load();
    RType::ConsoleModule *consoleModule = consoleModuleLoader.load();
    RType::ParticleModule *particleModule = particleModuleLoader.load();
    RType::IGraphicalModule *graphicalModule = graphicalModuleLoader.load();
    RType::GameView view(graphicalModule, ioContext, endpoint);

    logInformation("Hello, World for client!");
    soundModule->load();
    consoleModule->load();
    particleModule->load();
    graphicalModule->load();
    ioContext.run();
    view.start();
    soundModule->unload();
    consoleModule->unload();
    particleModule->unload();
    consoleModuleLoader.unload();
    soundModuleLoader.unload();
    particleModuleLoader.unload();
    graphicalModule->unload();
}
