/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "../include/UDPServer.hpp"
#include <engine/network/NetworkMessage.hpp>

void RType::UDPServer::startReceive() {
    auto receiveData = [this](const boost::system::error_code &error, std::size_t bytes_received) {
        std::cout << "Receive " << bytes_received << "bytes!\n";
        if (!error)
            handleReceive(bytes_received);
        else std::cerr << "Error receiving message: " << error.message() << "\n";
        startReceive();
    };

    _adapter.receiveMessage(receiveData);
}

void RType::UDPServer::handleReceive(std::size_t bytesReceived) {
    const MessageBuffer &buffer = _adapter.getMessageBuffer();
    const std::vector<std::byte> receivedData(buffer.begin(), buffer.begin() + bytesReceived);
    const Message receiveMessage = Message::deserialize(receivedData);

    if (receiveMessage.type == MessageType::CONNECT) {
        const std::string sessionId = "id";
        const std::string messageData = "connect " + sessionId + " ok";
        const RType::Message message = RType::NetworkMessageBuilder(MessageType::CONNECT_CALLBACK)
                .setData(messageData)
                .build();
        const std::vector<std::byte> binaryData = message.serialize();

        std::cout << "New connection!\n";
        _adapter.sendData(asio::buffer(binaryData));
    } else _adapter.sendData(asio::buffer(buffer.data(), bytesReceived));
}

RType::UDPServer::UDPServer(asio::io_context &io_context, const UDP::endpoint &endpoint) :
        _socket(io_context, endpoint),
        _adapter(_socket, _remoteEndpoint) {
    startReceive();
}

RType::UDPServer::~UDPServer() {
    try {
        _socket.close();
    } catch (std::exception &exception) {
        std::cerr << "Unable to close server socket: " << exception.what() << "\n";
    }
}
