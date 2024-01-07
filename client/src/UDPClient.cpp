/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#include <utility>

#include "../include/UDPClient.hpp"

void RType::UDPClient::startReceive() {
    auto receiveData = [this](const asio::error_code &error, std::size_t bytes_received) {
        std::cout << "Receive " << bytes_received << "bytes!\n";
        if (!error) {
            handleReceive(bytes_received);
        } else std::cerr << "Error receiving message: " << error.message() << "\n";
    };

    _adapter->receiveMessage(receiveData);
}

void RType::UDPClient::handleReceive(std::size_t bytesReceived) {
    const MessageBuffer &buffer = _adapter->getMessageBuffer();
    const std::vector<std::byte> receivedData(buffer.begin(), buffer.begin() + bytesReceived);
    const Message receiveMessage = Message::deserialize(receivedData);
    auto handlerIt = _handlers.find(receiveMessage.type);

    if (handlerIt != _handlers.end()) {
        std::cout << "Handle message: " << receiveMessage.toString() << "\n";
        handlerIt->second(receiveMessage);
    } else std::cout << "Unknown message!\n";
    startReceive();
}

RType::UDPClient::UDPClient(const std::string &hostname, int port, std::string username) :
        _username(std::move(username)),
        _socket(UDP::socket(_context, UDP::endpoint(UDP::v4(), 0))) {
    const asio::ip::address &serverAddress = asio::ip::address::from_string(hostname);

    _endpoint = UDP::endpoint(serverAddress, static_cast<uint16_t>(port));
    _adapter = std::make_shared<RType::UDPAdapter>(_socket, _endpoint);

    setupHandlers();

    _thread.run([this](const std::string &hostname, int port) {
        const RType::Message message = RType::NetworkMessageBuilder(RType::MessageType::CONNECT)
                .setData("")
                .build();

        std::cout << "Try connecting to " << hostname << ":" << port << "\n";
        _adapter->sendData(message);
        startReceive();
        _context.run();
    }, hostname, port);
}

void RType::UDPClient::handleConnectCallbackMessage(const RType::Message &receiveMessage) {
    const std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int connectionId = std::stoi(splitMessage[1]);
    const std::string messageData = std::format("player {} {}\n", connectionId, _username);
    const RType::Message response = RType::NetworkMessageBuilder(MessageType::PLAYER_NAME)
            .setData(messageData)
            .build();
    const std::vector<std::byte> binaryData = response.serialize();

    _adapter->sendData(asio::buffer(binaryData));
    _clientID = connectionId;
}

void RType::UDPClient::handlePlayerNameCallbackMessageType(const RType::Message &receiveMessage) {
    _messageQueue.emplace_back(receiveMessage.toString());
}

void RType::UDPClient::setupHandlers() {
    _handlers[MessageType::UNKNOWN] = [](const Message &) { std::cout << "Unknown message!\n"; };
    _handlers[MessageType::CONNECT_CALLBACK] = [this](const Message &msg) { handleConnectCallbackMessage(msg); };
    _handlers[MessageType::PLAYER_NAME] = [this](const Message &msg) { handlePlayerNameCallbackMessageType(msg); };
}

std::string RType::UDPClient::getLastMessage() {
    std::lock_guard<std::mutex> lock(_queueMutex);

    if (!_messageQueue.empty()) {
        std::string message = _messageQueue.front();
        _messageQueue.erase(_messageQueue.begin());
        return message;
    } else {
        return "";
    }
}

void RType::UDPClient::sendMessage(RType::MessageType type, const std::string_view &data) {
    const RType::Message response = RType::NetworkMessageBuilder(type)
            .setData(data)
            .build();
    const std::vector<std::byte> binaryData = response.serialize();
    _adapter->sendData(asio::buffer(binaryData));
}
