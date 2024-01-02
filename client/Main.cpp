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
    RType::GameView view;
    RType::ModuleLoader<RType::SoundModule> soundModuleLoader("build/out/engine/modules/sound/libsound_module.so");
    RType::ModuleLoader<RType::ConsoleModule> consoleModuleLoader("build/out/engine/modules/console/libconsole_module.so");
    RType::ModuleLoader<RType::ParticleModule> particleModuleLoader("build/out/engine/modules/particle/libparticle_module.so");
    RType::ModuleLoader<RType::GraphicalModule> graphicalModuleLoader("build/out/engine/modules/graphical/libgraphical_module.so");
    RType::SoundModule *soundModule = soundModuleLoader.load();
    RType::ConsoleModule *consoleModule = consoleModuleLoader.load();
    RType::ParticleModule *particleModule = particleModuleLoader.load();
    RType::GraphicalModule *graphicalModule = graphicalModuleLoader.load();

    logInformation("Hello, World for client!");
    soundModule->load();
    consoleModule->load();
    particleModule->load();
    graphicalModule->load();

    asio::io_context ioContext;
    UDP::socket socket(ioContext, UDP::endpoint(UDP::v4(), 0));
    UDP::endpoint serverEndpoint(asio::ip::address::from_string("127.0.0.1"), 9002);
    RType::UDPAdapter adapter(socket, serverEndpoint);

    const RType::Message message = RType::NetworkMessageBuilder(RType::MessageType::CONNECT)
            .setData("")
            .build();

    adapter.sendData(message);
    view.start();

    soundModule->unload();
    consoleModule->unload();
    particleModule->unload();
    consoleModuleLoader.unload();
    soundModuleLoader.unload();
    particleModuleLoader.unload();
    graphicalModule->unload();
}
