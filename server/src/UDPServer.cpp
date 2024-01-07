/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "../include/UDPServer.hpp"
#include <engine/network/NetworkMessage.hpp>

void RType::UDPServer::startReceive() {
    auto receiveData = [this](const asio::error_code &error, std::size_t bytes_received) {
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
    _handlers[MessageType::PLAYER_NAME] = [this](const Message& msg) {handlePlayerNameMessageType(msg);};
    _handlers[MessageType::MOVE_LEFT] = [this](const Message& msg) {handleMoveLeftMessageType(msg);};
    _handlers[MessageType::MOVE_RIGHT] = [this](const Message& msg) {handleMoveRightMessageType(msg);};
    _handlers[MessageType::MOVE_DOWN] = [this](const Message& msg) {handleMoveDownMessageType(msg);};
    _handlers[MessageType::MOVE_UP] = [this](const Message& msg) {handleMoveUpMessageType(msg);};
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

    std::cout << "New connection! SessionId: " << sessionId << "!\n";
    sendMessage(MessageType::CONNECT_CALLBACK, std::format("connect {} ok", sessionId));
}

void RType::UDPServer::handleUnknownMessageType(const RType::Message &) {
    std::cout << "Unknown Message!\n";
}

void RType::UDPServer::handlePlayerNameMessageType(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    std::string playerName = splitMessage[2];
    std::shared_ptr<Client> session = _sessions.getClientSession(sessionID);

    session->setPlayerName(playerName);
    session->setPlayerEntity(createPlayerEntity(sessionID));
}

void RType::UDPServer::sendMessage(MessageType type, const std::string_view &data) {
    const RType::Message response = RType::NetworkMessageBuilder(type)
            .setData(data)
            .build();
    const std::vector<std::byte> binaryData = response.serialize();
    _adapter.sendData(asio::buffer(binaryData));
}

void RType::UDPServer::handleMoveLeftMessageType(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    std::shared_ptr<Client> session = _sessions.getClientSession(sessionID);

    sendMessage(MessageType::MOVE_LEFT, std::format("move_left {} ok\n", sessionID));
    std::cout << session->getPlayerName() << ": Move Left!\n";
}

void RType::UDPServer::handleMoveRightMessageType(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    std::shared_ptr<Client> session = _sessions.getClientSession(sessionID);

    sendMessage(MessageType::MOVE_RIGHT, std::format("move_right {} ok\n", sessionID));
    std::cout << session->getPlayerName() << ": Move Right!\n";
}

void RType::UDPServer::handleMoveDownMessageType(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    std::shared_ptr<Client> session = _sessions.getClientSession(sessionID);

    sendMessage(MessageType::MOVE_DOWN, std::format("move_down {} ok\n", sessionID));
    std::cout << session->getPlayerName() << ": Move Down!\n";
}

void RType::UDPServer::handleMoveUpMessageType(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    std::shared_ptr<Client> session = _sessions.getClientSession(sessionID);

    sendMessage(MessageType::MOVE_DOWN, std::format("move_up {} ok\n", sessionID));
    std::cout << session->getPlayerName() << ": Move Up!\n";
}

RType::EntityPtr RType::UDPServer::createPlayerEntity(int sessionID) {
    EntityPtr playerEntity = _entityManager.createEntity();
    std::string message = std::format("player {} speed 10 health 100 position 300 30 size 2 2", sessionID);

    playerEntity->addComponent<SpeedComponent>(10);
    playerEntity->addComponent<HealthComponent>(100);
    playerEntity->addComponent<PositionComponent>(std::make_pair(300, 30));
    playerEntity->addComponent<SizeComponent>(2.0f, 2.0f);
    playerEntity->addComponent<PlayerComponent>(true);
    sendMessage(MessageType::PLAYER_NAME, message);
    return playerEntity;
}
