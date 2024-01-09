/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "../../include/network/MessageParser.hpp"
#include "../../include/SessionManager.hpp"
#include "engine/tools/Split.hpp"

RType::MessageParser::MessageParser(GameLogic *game, UDPAdapter *adapter) :
        _game(game),
        _adapter(adapter),
        _sessions(&game->getSessionManager()) {
    _handlers[MessageType::CONNECT] = [this](const Message &msg) { handleConnectMessage(msg); };
    _handlers[MessageType::DISCONNECT] = [this](const Message &) { sendMessage(MessageType::DISCONNECT, ""); };
    _handlers[MessageType::UNKNOWN] = [this](const Message &msg) { handleUnknownMessageType(msg); };
    _handlers[MessageType::PLAYER_NAME] = [this](const Message &msg) { handlePlayerNameMessageType(msg); };
    _handlers[MessageType::MOVE_LEFT] = [this](const Message &msg) { handleMove(msg); };
    _handlers[MessageType::MOVE_RIGHT] = [this](const Message &msg) { handleMove(msg); };
    _handlers[MessageType::MOVE_DOWN] = [this](const Message &msg) { handleMove(msg); };
    _handlers[MessageType::MOVE_UP] = [this](const Message &msg) { handleMove(msg); };
    _handlers[MessageType::SHOOT] = [this](const Message &msg) { handleShoot(msg); };
}

void RType::MessageParser::handleConnectMessage(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionId = _sessions->getNextSessionId();
    float windowWidth = std::stof(splitMessage[1]);
    float windowHeight = std::stof(splitMessage[2]);
    std::shared_ptr<Client> session = _sessions->getClientSession(sessionId);

    session->setWindowWidth(windowWidth);
    session->setWindowHeight(windowHeight);
    std::cout << "New connection! SessionId: " << sessionId << "!\n";
    sendMessage(MessageType::CONNECT_CALLBACK, std::format("connect {} ok", sessionId));
}

void RType::MessageParser::handleUnknownMessageType(const RType::Message &) {
    std::cout << "Unknown Message!\n";
}

void RType::MessageParser::handlePlayerNameMessageType(const RType::Message &receiveMessage) {
    const std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    const int sessionID = std::stoi(splitMessage[1]);
    const std::string playerName = splitMessage[2];
    const RType::Session session = _sessions->getClientSession(sessionID);

    session->setPlayerName(playerName);
    session->setPlayerEntity(createPlayerEntity(sessionID));
}

void RType::MessageParser::handleMove(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    Session session = _sessions->getClientSession(sessionID);
    EntityPtr entity = session->getEntity();
    bool move = entity->move(getDirection(receiveMessage.type), _game->getEntityManager().getEntities(), session->getWindowWidth(), session->getWindowHeight());
    std::string status = (move ? "ok" : "ko");

    sendMessage(receiveMessage.type, std::format("{} {} {}\n", splitMessage[0], sessionID, status));
}

void RType::MessageParser::parseMessage(const RType::MessageBuffer &buffer, std::size_t bytesReceived) {
    const std::vector<std::byte> receivedData(buffer.begin(), buffer.begin() + bytesReceived);
    const Message receiveMessage = Message::deserialize(receivedData);
    auto handlerIt = _handlers.find(receiveMessage.type);

    if (handlerIt != _handlers.end())
        handlerIt->second(receiveMessage);
    else
        handleUnknownMessageType(receiveMessage);
}

void RType::MessageParser::sendMessage(MessageType type, const std::string_view &data) {
    const RType::Message response = RType::NetworkMessageBuilder(type)
            .setData(data)
            .build();
    const std::vector<std::byte> binaryData = response.serialize();

    _adapter->sendData(asio::buffer(binaryData));
}

RType::EntityPtr RType::MessageParser::createPlayerEntity(int sessionID) {
    const std::string message = std::format("player {} speed 10 health 100 position 300 30 size 2 2 rect 33 15", sessionID);
    EntityPtr playerEntity = _game->getFactory().createDefaultPlayer();

    sendMessage(MessageType::PLAYER_NAME, message);
    return playerEntity;
}

void RType::MessageParser::handleShoot(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);

    createBulletEntity(sessionID);
}

RType::EntityPtr RType::MessageParser::createBulletEntity(int sessionID) {
    const std::string message = std::format("shoot {} speed 10 damage 20 ok", sessionID);
    EntityPtr bulletEntity = _game->getFactory().createBullet();

    sendMessage(MessageType::SHOOT, message);
    return bulletEntity;
}

RType::Direction RType::MessageParser::getDirection(RType::MessageType type) {
    using enum RType::Direction;
    switch (type) {
        case RType::MessageType::MOVE_LEFT:
            return LEFT;
        case RType::MessageType::MOVE_RIGHT:
            return RIGHT;
        case RType::MessageType::MOVE_DOWN:
            return DOWN;
        case RType::MessageType::MOVE_UP:
            return UP;
        default:
            return RIGHT;
    }
}
