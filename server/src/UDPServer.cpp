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

    auto handlerIt = _handlers.find(receiveMessage.type);
    if (handlerIt != _handlers.end())
        handlerIt->second(receiveMessage);
    else
        handleUnknownMessageType(receiveMessage);
}

RType::UDPServer::UDPServer(asio::io_context &io_context, const UDP::endpoint &endpoint) :
        _socket(io_context, endpoint),
        _adapter(_socket, _remoteEndpoint) {
    _handlers[MessageType::CONNECT] = [this](const Message& msg) {handleConnectMessage(msg);};
    _handlers[MessageType::UNKNOWN] = [this](const Message& msg) {handleUnknownMessageType(msg);};
    startReceive();
}

RType::UDPServer::~UDPServer() {
    try {
        _socket.close();
    } catch (std::exception &exception) {
        std::cerr << "Unable to close server socket: " << exception.what() << "\n";
    }
}

void RType::UDPServer::handleConnectMessage(const RType::Message &) {
    int sessionId = _sessions.setNewSession();
    const std::string messageData = std::format("connect {} ok", sessionId);
    const RType::Message response = RType::NetworkMessageBuilder(MessageType::CONNECT_CALLBACK)
            .setData(messageData)
            .build();
    const std::vector<std::byte> binaryData = response.serialize();

    std::cout << "New connection!\n";
    _adapter.sendData(asio::buffer(binaryData));
}

void RType::UDPServer::handleUnknownMessageType(const RType::Message &) {
    const RType::Message response = RType::NetworkMessageBuilder(MessageType::UNKNOWN)
            .setData("Unknown Message!")
            .build();
    const std::vector<std::byte> binaryData = response.serialize();
    _adapter.sendData(asio::buffer(binaryData));
}
