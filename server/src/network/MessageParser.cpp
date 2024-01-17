/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "../../include/network/MessageParser.hpp"
#include "../../include/SessionManager.hpp"
#include "engine/ecs/component/SizeRectComponent.hpp"
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
    _handlers[MessageType::PLAYER_COLOR] = [this](const Message &msg) { handlePlayerColor(msg); };
    _handlers[MessageType::TICK] = [this](const Message &msg) { handleTick(msg); };
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
    session->setPlayerEntity(createPlayerEntity(sessionID, session));
    sendAllMessages(sessionID);
    sendAllEntities(sessionID);
}

void RType::MessageParser::handleMove(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    Session session = _sessions->getClientSession(sessionID);
    EntityPtr entity = session->getEntity();
    std::string status = "ok";

    sendAllMessages(sessionID);
    entity->move(getDirection(receiveMessage.type), _game->getEntityManager().getEntities(), session->getWindowWidth(), session->getWindowHeight());
    char buffer[50];
    sprintf(buffer, "%s %d %s\n", splitMessage[0].c_str(), sessionID, status.c_str());
    sendMessage(receiveMessage.type, buffer);
    checkEntitiesStatus();
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

RType::EntityPtr RType::MessageParser::createPlayerEntity(int sessionID, const Session &session) {
    EntityPtr playerEntity = _game->getFactory().createDefaultPlayer(session->getPlayerName());
    char buffer[50];

    sprintf(buffer, "turquoisePlayer %d\n", sessionID);
    playerEntity->setEntityName(buffer);
    sendPlayerDetails(playerEntity);
    return playerEntity;
}

void RType::MessageParser::handleShoot(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector <std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);

    sendAllMessages(sessionID);
    if (!createBulletPlayerEntity(sessionID)) {
        char buffer[50];
        sprintf(buffer, "shoot %d ko\n", sessionID);
        sendMessage(MessageType::SHOOT, buffer);
    }
}

bool RType::MessageParser::createBulletPlayerEntity(int sessionID) {
    const std::string message;
    char buffer[50];
    sprintf(buffer, "shoot %d ko\n", sessionID);
    const std::string messageFailure(buffer);
    Session session = _sessions->getClientSession(sessionID);
    EntityPtr player = session->getEntity();
    bool shoot = player->canShoot(_game->getEntityManager().getEntities(), "bulletPlayer");
    auto [playerX, playerY] = player->getComponent<PositionComponent>()->getPositions();
    float playerSizeX = player->getComponent<SizeComponent>()->getSize().first;
    float playerRectX = player->getComponent<SizeRectComponent>()->getSize().first;
    float playerRectY = player->getComponent<SizeRectComponent>()->getSize().second;
    float startX = playerX + (playerRectX * playerSizeX);
    float startY = playerY + playerRectY;
    EntityPtr bulletEntity;

    if (shoot) {
        bulletEntity = _game->getFactory().createBulletPlayer(startX, startY);
        char bulletName[100];
        sprintf(bulletName, "bulletPlayer %d", sessionID);
        bulletEntity->setEntityName(bulletName);
        char buffer[200];
        sprintf(buffer, "shoot %d speed 10 damage 20 position %.2f %.2f size 1 1 rect 14 14 ok\n", sessionID, startX, startY);
        sendMessage(MessageType::SHOOT, buffer);    }
    return shoot;
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

void RType::MessageParser::handlePlayerColor(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    Session session = _sessions->getClientSession(sessionID);

    sendAllMessages(sessionID);
    session->setNextColor();
    char entityName[50];
    sprintf(entityName, "%sPlayer %d", session->getColor().c_str(), sessionID);
    session->getEntity()->setEntityName(entityName);
    char buffer[50];
    sprintf(buffer, "color %d %s\n", sessionID, session->getColor().c_str());
    sendMessage(MessageType::PLAYER_COLOR, buffer);
}

RType::SessionManager *RType::MessageParser::getSessionManager() {
    return _sessions;
}

void RType::MessageParser::checkEntitiesStatus() {
    auto entities = _game->getEntityManager().getEntities();
    std::vector<EntityPtr> toDestroy;

    for (auto &entity: entities) {
        if (entity->getDeathStatus()) {
            toDestroy.emplace_back(entity);
            char buffer[100];
            sprintf(buffer, "death %s\n", entity->getEntityName().c_str());
            sendMessage(MessageType::DEATH, buffer);
        }
    }
    for (auto &entity: toDestroy)
        _game->getEntityManager().destroyEntity(entity);
}

void RType::MessageParser::sendAllMessages(int sessionID) {
    Session client = _sessions->getClientSession(sessionID);
    Message message = client->getLastMessage();

    while (message.type != MessageType::NULLDATA) {
        _adapter->sendData(message);
        message = client->getLastMessage();
    }
}

void RType::MessageParser::addMessageClients(int sessionID, MessageType type, const std::string_view &data) {
    for (auto &client : _sessions->getSessions()) {
        if (client.first != sessionID && client.second != nullptr)
            client.second->addMessage(NetworkMessageBuilder(type)
                                              .setData(data)
                                              .build());
    }
}

void RType::MessageParser::handleTick(const RType::Message &receiveMessage) {
    const std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    const int sessionID = std::stoi(splitMessage[1]);

    sendAllMessages(sessionID);
}

void RType::MessageParser::sendAllEntities(int sessionID) {
    Session client = _sessions->getClientSession(sessionID);

    for (auto &entity : _game->getEntityManager().getEntities())
        sendMessageFromEntity(entity);
}

void RType::MessageParser::sendMessageFromEntity(const RType::EntityPtr& entity) {
    std::vector<std::string> entityName = Split::split(entity->getEntityName(), " ");

    if (entityName[0] == "turquoisePlayer" || entityName[0] == "purplePlayer" || entityName[0] == "greenPlayer" || entityName[0] == "redPlayer" || entityName[0] == "bluePlayer")
        sendPlayerDetails(entity);
    if (entityName[0] == "bulletPlayer")
        std::cout << "todo\n";
}

void RType::MessageParser::sendPlayerDetails(const RType::EntityPtr& entity) {
    char id[250];
    std::vector<std::string> entityName = Split::split(entity->getEntityName(), " ");
    int speed = entity->getComponent<SpeedComponent>()->getSpeed();
    int health = entity->getComponent<HealthComponent>()->getHealth();
    auto [playerX, playerY] = entity->getComponent<PositionComponent>()->getPositions();
    auto [sizeX, sizeY] = entity->getComponent<SizeComponent>()->getSize();
    auto [sizeRectX, sizeRectY] = entity->getComponent<SizeRectComponent>()->getSize();
    std::string playerName = entity->getComponent<PlayerComponent>()->getUserName();
    int score = entity->getComponent<PlayerComponent>()->getScore();

    sprintf(id, "player %s speed %d health %d position %d %d size %f %f rect %f %f color %s name %s score %d\n",
            entityName[1].c_str(),
            speed,
            health,
            playerX,
            playerY,
            sizeX,
            sizeY,
            sizeRectX,
            sizeRectY,
            entityName[0].c_str(),
            playerName.c_str(),
            score);
    sendMessage(MessageType::PLAYER_NAME, id);
    addMessageClients(std::stoi(entityName[1]), MessageType::PLAYER_NAME, id);
}
