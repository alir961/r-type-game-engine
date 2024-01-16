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
        if (!error) {
            handleReceive(bytes_received);
        } else std::cerr << "Error receiving message: " << error.message() << "\n";
    };

    if (_stop) return;
    _adapter.receiveMessage(receiveData);
}

void RType::UDPClient::handleReceive(std::size_t bytesReceived) {
    const MessageBuffer &buffer = _adapter.getMessageBuffer();
    const std::vector<std::byte> receivedData(buffer.begin(), buffer.begin() + bytesReceived);
    const Message receiveMessage = Message::deserialize(receivedData);

    if (_handlers.contains(receiveMessage.type))
        _handlers[receiveMessage.type](receiveMessage);
    else std::cout << "Unknown message!\n";
    if (_stop) return;
    startReceive();
}

RType::UDPClient::UDPClient(const std::string &hostname, int port, std::string username, float windowWidth, float windowHeight) :
        _username(std::move(username)), _adapter(hostname, static_cast<uint16_t>(port)), _windowWidth(windowWidth), _windowHeight(windowHeight) {
    setupHandlers();

    _thread.run([this, hostname, port]() {
        char buffer[50];
        sprintf(buffer, "connect %.2f %.2f\n", _windowWidth, _windowHeight);
        const RType::Message message = RType::NetworkMessageBuilder(RType::MessageType::CONNECT)
                .setData(buffer)
                .build();

        std::cout << "Try connecting to " << hostname << ":" << port << "\n";
        _adapter.sendData(message);
        startReceive();
        _adapter.runContext();
    });
}

RType::UDPClient::~UDPClient() {
    const RType::Message message = RType::NetworkMessageBuilder(RType::MessageType::DISCONNECT)
            .setData("")
            .build();

    try {
        _stop = true;
        _adapter.sendData(message);
        _thread.wait();
        _adapter.closeSocket();
    } catch (const std::exception &e) {
        std::cerr << "Unable to close UDP client: " << e.what() << "\n";
    }
}

void RType::UDPClient::handleConnectCallbackMessage(const RType::Message &receiveMessage) {
    const std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int connectionId = std::stoi(splitMessage[1]);
    char buffer[50];
    sprintf(buffer, "player %d %s\n", connectionId, _username.c_str());
    const std::string messageData = buffer;
    const RType::Message response = RType::NetworkMessageBuilder(MessageType::PLAYER_NAME)
            .setData(messageData)
            .build();

    _adapter.sendData(response);
    _clientID = connectionId;
    _connected = true;
}

void RType::UDPClient::setupHandlers() {
    _handlers[MessageType::UNKNOWN] = [](const Message &) { std::cout << "Unknown message!\n"; };
    _handlers[MessageType::CONNECT_CALLBACK] = [this](const Message &msg) { handleConnectCallbackMessage(msg); };
    _handlers[MessageType::PLAYER_NAME] = [this](const Message &msg) { addMessageQueue(msg); };
    _handlers[MessageType::MOVE_LEFT] = [this](const Message &msg) { addMessageQueue(msg); };
    _handlers[MessageType::MOVE_RIGHT] = [this](const Message &msg) { addMessageQueue(msg); };
    _handlers[MessageType::MOVE_UP] = [this](const Message &msg) { addMessageQueue(msg); };
    _handlers[MessageType::MOVE_DOWN] = [this](const Message &msg) { addMessageQueue(msg); };
    _handlers[MessageType::PLAYER_COLOR] = [this](const Message &msg) { addMessageQueue(msg); };
    _handlers[MessageType::DISCONNECT] = [this](const Message &) { _stop = true; };
    _handlers[MessageType::SHOOT] = [this](const Message &msg) { addMessageQueue(msg); };
    _handlers[MessageType::DEATH] = [this](const Message &msg) { addMessageQueue(msg); };
    _handlers[MessageType::MOVE_PLAYER_BULLET] = [this](const Message &msg) { addMessageQueue(msg); };
}

std::string RType::UDPClient::getLastMessage() {
    const std::lock_guard lock(_queueMutex);

    if (!_messageQueue.empty()) {
        std::string message = _messageQueue.front();
        _messageQueue.erase(_messageQueue.begin());
        return message;
    }
    return "";
}

std::vector<std::string> RType::UDPClient::pullQueue() {
    std::vector<std::string> messages;
    std::string message = getLastMessage();

    do {
        messages.push_back(message);
        message = getLastMessage();
    } while (!message.empty());
    return messages;
}

void RType::UDPClient::sendMessage(RType::MessageType type, const std::string_view &data) {
    const RType::Message response = RType::NetworkMessageBuilder(type)
            .setData(data)
            .build();
    const std::vector<std::byte> binaryData = response.serialize();

    _adapter.sendData(response);
}

void RType::UDPClient::addMessageQueue(const RType::Message &receiveMessage) {
    const std::scoped_lock lock(_queueMutex);

    _messageQueue.push_back(receiveMessage.toString());
}
