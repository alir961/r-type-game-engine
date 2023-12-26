#include <engine/Logger.hpp>
#include <engine/network/UDPAdapter.hpp>
#include "include/GameView.hpp"
#include "engine/network/NetworkMessage.hpp"

int main() {
    RType::GameView view;

    logInformation("Hello, World for client!");

    asio::io_context ioContext;
    UDP::socket socket(ioContext, UDP::endpoint(UDP::v4(), 0));
    UDP::endpoint serverEndpoint(asio::ip::address::from_string("127.0.0.1"), 9002);
    RType::UDPAdapter adapter(socket, serverEndpoint);

    const RType::Message message = RType::NetworkMessageBuilder(RType::MessageType::CONNECT)
            .setData("")
            .build();

    adapter.sendData(message);
    view.start();
}
