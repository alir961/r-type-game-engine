/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "../../include/network/MessageParser.hpp"
#include "engine/tools/Split.hpp"

RType::MessageParser::MessageParser(GameLogic *game, UDPAdapter *adapter) :
        _game(game),
        _adapter(adapter),
        _sessions(&game->getSessionManager()) {
    _handlers[MessageType::CONNECT] = [this](const Message &msg) { handleConnectMessage(msg); };
    _handlers[MessageType::UNKNOWN] = [this](const Message &msg) { handleUnknownMessageType(msg); };
    _handlers[MessageType::PLAYER_NAME] = [this](const Message &msg) { handlePlayerNameMessageType(msg); };
    _handlers[MessageType::MOVE_LEFT] = [this](const Message &msg) { handleMove(msg); };
    _handlers[MessageType::MOVE_RIGHT] = [this](const Message &msg) { handleMove(msg); };
    _handlers[MessageType::MOVE_DOWN] = [this](const Message &msg) { handleMove(msg); };
    _handlers[MessageType::MOVE_UP] = [this](const Message &msg) { handleMove(msg); };
    _handlers[MessageType::SHOOT] = [this](const Message &msg) { handlePlayerShoot(msg); };
    _handlers[MessageType::PLAYER_COLOR] = [this](const Message &msg) { handlePlayerColor(msg); };
    _handlers[MessageType::TICK] = [this](const Message &msg) { handleTick(msg); };
    _handlers[MessageType::DISCONNECT] = [this](const Message &msg) { handleDisconnect(msg); };
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
    if (_sessions->getWindowWidth() < windowWidth)
        _sessions->setWindowWidth(windowWidth);
    if (_sessions->getWindowHeight() < windowHeight)
        _sessions->setWindowHeight(windowHeight);
    std::cout << "New connection! SessionId: " << sessionId << "!\n";
    char buffer[50];
    sprintf(buffer, "connect %d ok", sessionId);
    sendMessage(MessageType::CONNECT_CALLBACK, buffer);}

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
    if (session->getEntity() == nullptr)
        session->setPlayerEntity(_game->createPlayerEntity(sessionID, session));
    _game->sendAllMessages(sessionID);
    _game->sendAllEntities(sessionID);
}

void RType::MessageParser::handleMove(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    Session session = _sessions->getClientSession(sessionID);
    EntityPtr entity = session->getEntity();

    if (entity == nullptr)
        return;
    _game->sendAllMessages(sessionID);
    entity->move(_game->getDirection(receiveMessage.type), _game->getEntityManager().getEntities(), session->getWindowWidth(), session->getWindowHeight());
    _game->sendPlayerDetails(entity);
    _game->checkEntitiesStatus(session);
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
    _adapter->sendData(response);
}

void RType::MessageParser::handlePlayerColor(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    Session session = _sessions->getClientSession(sessionID);

    _game->sendAllMessages(sessionID);
    session->setNextColor();
    char entityName[50];
    sprintf(entityName, "%sPlayer %d", session->getColor().c_str(), sessionID);
    session->getEntity()->setEntityName(entityName);
    char buffer[50];
    sprintf(buffer, "color %d %s\n", sessionID, session->getColor().c_str());
    sendMessage(MessageType::PLAYER_COLOR, buffer);
}

void RType::MessageParser::handleTick(const RType::Message &receiveMessage) {
    const std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    const int sessionID = std::stoi(splitMessage[1]);

    _game->sendAllMessages(sessionID);
}

void RType::MessageParser::handlePlayerShoot(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector <std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);

    _game->sendAllMessages(sessionID);
    _game->createBulletPlayerEntity(sessionID);
}

void RType::MessageParser::handleDisconnect(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector <std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    EntityPtr playerEntity = _sessions->getClientSession(sessionID)->getEntity();

    if (playerEntity == nullptr)
        sendMessage(MessageType::DISCONNECT, "disconnect\n");
    else
        sendMessage(MessageType::DISCONNECT, "disconnect " + playerEntity->getEntityName() + "\n");
    _game->getEntityManager().destroyEntity(playerEntity);
    _sessions->deleteSession(sessionID);
    std::cout << "SessionID " + std::to_string(sessionID) + " disconnected!\n";
}
