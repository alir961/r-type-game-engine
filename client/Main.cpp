#include "include/ClientViewport.hpp"
#include <engine/Logger.hpp>
#include <engine/network/UDPAdapter.hpp>
#include <engine/modules/ModuleLoader.hpp>
#include <engine/modules/ModuleProvider.hpp>

int main() {
    asio::io_context ioContext;
    const asio::ip::address &serverAddress = asio::ip::address::from_string("127.0.0.1");
    const UDP::endpoint endpoint(serverAddress, 9002);
    RType::ModuleProvider provider;
    auto *graphicalModule = provider.loadAndGetModule<RType::IGraphicalModule>(RType::ModuleType::GRAPHICAL);
    RType::ClientViewport view(graphicalModule, ioContext, endpoint);

    logInformation("Hello, World for client!");
    ioContext.run();
    view.start();
}
