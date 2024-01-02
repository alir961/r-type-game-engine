/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#include "../include/UDPClient.hpp"

void RType::UDPClient::startReceive() {
    auto receiveData = [this](const boost::system::error_code &error, std::size_t bytes_received) {
        std::cout << "Receive " << bytes_received << "bytes!\n";
        if (!error) {
            handleReceive(bytes_received);
        }
        else std::cerr << "Error receiving message: " << error.message() << "\n";
    };
    _adapter.receiveMessage(receiveData);
}

void RType::UDPClient::handleReceive(std::size_t bytesReceived) {
    const MessageBuffer &buffer = _adapter.getMessageBuffer();
    const std::vector<std::byte> receivedData(buffer.begin(), buffer.begin() + bytesReceived);
    const Message receiveMessage = Message::deserialize(receivedData);

    auto handlerIt = _handlers.find(receiveMessage.type);
    if (handlerIt != _handlers.end())
        handlerIt->second(receiveMessage);
    else
        handleUnknownMessageType(receiveMessage);
}

RType::UDPClient::UDPClient(asio::io_context &io_context, UDP::endpoint endpoint) :
    _socket(io_context, UDP::endpoint(UDP::v4(), 0)),
    _adapter(_socket, endpoint) {
    _handlers[MessageType::CONNECT_CALLBACK] = [this](const Message& msg) {handleConnectCallbackMessage(msg);};
    _handlers[MessageType::UNKNOWN] = [this](const Message& msg) {handleUnknownMessageType(msg);};
    _handlers[MessageType::PLAYER_NAME] = [this](const Message& msg) {handlePlayerNameCallbackMessageType(msg);};
    const RType::Message message = RType::NetworkMessageBuilder(RType::MessageType::CONNECT)
            .setData("")
            .build();
    _adapter.sendData(message);
    startReceive();
}

void RType::UDPClient::handleConnectCallbackMessage(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int connectionId = std::stoi(splitMessage[1]);
    const std::string messageData = std::format("player {} {}\n", connectionId, "Zeubio");
    const RType::Message response = RType::NetworkMessageBuilder(MessageType::PLAYER_NAME)
            .setData(messageData)
            .build();
    const std::vector<std::byte> binaryData = response.serialize();

    _adapter.sendData(asio::buffer(binaryData));
    std::cout << "Connection ID: " << connectionId << "\n";
}

void RType::UDPClient::handleUnknownMessageType(const RType::Message &) {
    std::cout << "Unknown message!" << "\n";
}

void RType::UDPClient::handlePlayerNameCallbackMessageType(const RType::Message &receiveMessage) {
    std::cout << receiveMessage.toString();
}
