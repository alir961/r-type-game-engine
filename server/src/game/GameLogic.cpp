/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#include "../../include/game/GameLogic.hpp"

extern "C" {
bool _stop = false;

void stopServer(int) {
    if (_stop) exit(EXIT_FAILURE);
    std::cout << "Stopping the server [...]\n";
    _stop = true;
}
}

RType::GameLogic::GameLogic(RType::UDPAdapter *adapter) : _adapter(adapter) {
    signal(SIGINT, &stopServer);

    _thread.run([this]() { serverLoopIterate(); });
}

void RType::GameLogic::serverLoopIterate() {
    if (_stop) return;

    std::this_thread::sleep_for(std::chrono::milliseconds(EPSILON_TIME_MS));
    _tickNumber++;
    moveBulletPlayer();
    serverLoopIterate();
}


bool RType::GameLogic::isStopped() {
    if (_stop)
        _thread.wait();
    return _stop;
}

void RType::GameLogic::moveBulletPlayer() {
    for (auto &entity: _entityManager.getEntities()) {
        if (Split::split(entity->getEntityName(), " ")[0] == "bulletPlayer") {
            entity->move(Direction::RIGHT, _entityManager.getEntities(), _sessionManager.getWindowWidth(),
                         _sessionManager.getWindowHeight());
            sendBulletPlayerDetails(entity);
            checkEntitiesStatus(nullptr);
        }
    }
}

void RType::GameLogic::sendMessage(RType::MessageType type, const std::string_view &data) {
    const RType::Message response = RType::NetworkMessageBuilder(type)
            .setData(data)
            .build();
    _adapter->sendData(response);
}

RType::EntityPtr RType::GameLogic::createPlayerEntity(int sessionID, const RType::Session &session) {
    EntityPtr playerEntity = getFactory().createDefaultPlayer(session->getPlayerName());
    char buffer[50];

    sprintf(buffer, "turquoisePlayer %d\n", sessionID);
    playerEntity->setEntityName(buffer);
    sendPlayerDetails(playerEntity);
    return playerEntity;
}

void RType::GameLogic::createBulletPlayerEntity(int sessionID) {
    const std::string message;
    Session session = _sessionManager.getClientSession(sessionID);
    EntityPtr player = session->getEntity();
    if (player == nullptr) return;
    auto [playerX, playerY] = player->getComponent<PositionComponent>()->getPositions();
    float playerSizeX = player->getComponent<SizeComponent>()->getSize().first;
    float playerRectX = player->getComponent<SizeRectComponent>()->getSize().first;
    float playerRectY = player->getComponent<SizeRectComponent>()->getSize().second;
    float startX = playerX + (playerRectX * playerSizeX);
    float startY = playerY + playerRectY;
    EntityPtr bulletEntity;
    char bulletName[200];

    bulletEntity = getFactory().createBulletPlayer(startX, startY);
    sprintf(bulletName, "bulletPlayer %d %d", sessionID, session->getNextBulletID());
    bulletEntity->setEntityName(bulletName);
    sendBulletPlayerDetails(bulletEntity);
}

RType::Direction RType::GameLogic::getDirection(RType::MessageType type) {
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

void RType::GameLogic::checkEntitiesStatus(Session session) {
    auto entities = getEntityManager().getEntities();
    std::vector<EntityPtr> toDestroy;

    for (auto &entity: entities) {
        if (entity->getDeathStatus()) {
            if (session != nullptr && session->getEntity() == entity)
                session->setPlayerEntity(nullptr);
            toDestroy.emplace_back(entity);
            char buffer[100];
            sprintf(buffer, "death %s\n", entity->getEntityName().c_str());
            addMessageClients(-1, MessageType::DEATH, buffer);
        }
    }
    for (auto &entity: toDestroy)
        getEntityManager().destroyEntity(entity);
}

void RType::GameLogic::sendAllMessages(int sessionID) {
    Session client = _sessionManager.getClientSession(sessionID);
    Message message = client->getLastMessage();

    while (message.type != MessageType::NULLDATA) {
        _adapter->sendData(message);
        message = client->getLastMessage();
    }
}

void RType::GameLogic::sendAllEntities(int sessionID) {
    Session client = _sessionManager.getClientSession(sessionID);

    for (auto &entity : getEntityManager().getEntities())
        sendMessageFromEntity(entity);
}

void RType::GameLogic::sendMessageFromEntity(const RType::EntityPtr &entity) {
    std::vector<std::string> entityName = Split::split(entity->getEntityName(), " ");

    if (entityName[0] == "turquoisePlayer" || entityName[0] == "purplePlayer" || entityName[0] == "greenPlayer" || entityName[0] == "redPlayer" || entityName[0] == "bluePlayer")
        sendPlayerDetails(entity);
    if (entityName[0] == "bulletPlayer")
        sendBulletPlayerDetails(entity);
}

void RType::GameLogic::addMessageClients(int sessionID, RType::MessageType type, const std::string_view &data) {
    for (auto &client : _sessionManager.getSessions()) {
        if (client.first != sessionID && client.second != nullptr)
            client.second->addMessage(NetworkMessageBuilder(type)
                                              .setData(data)
                                              .build());
    }
}

void RType::GameLogic::sendPlayerDetails(const RType::EntityPtr &entity) {
    char details[250];
    std::vector<std::string> entityName = Split::split(entity->getEntityName(), " ");
    int speed = entity->getComponent<SpeedComponent>()->getSpeed();
    int health = entity->getComponent<HealthComponent>()->getHealth();
    auto [playerX, playerY] = entity->getComponent<PositionComponent>()->getPositions();
    auto [sizeX, sizeY] = entity->getComponent<SizeComponent>()->getSize();
    auto [sizeRectX, sizeRectY] = entity->getComponent<SizeRectComponent>()->getSize();
    std::string playerName = entity->getComponent<PlayerComponent>()->getUserName();
    int score = entity->getComponent<PlayerComponent>()->getScore();

    sprintf(details, "player %s speed %d health %d position %d %d size %f %f rect %f %f color %s name %s score %d\n",
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
    sendMessage(MessageType::PLAYER_NAME, details);
    addMessageClients(std::stoi(entityName[1]), MessageType::PLAYER_NAME, details);
}

void RType::GameLogic::sendBulletPlayerDetails(const RType::EntityPtr &entity) {
    char details[250];
    std::vector<std::string> entityName = Split::split(entity->getEntityName(), " ");
    int speed = entity->getComponent<SpeedComponent>()->getSpeed();
    int damage = entity->getComponent<DamageComponent>()->getDamage();
    auto [entityX, entityY] = entity->getComponent<PositionComponent>()->getPositions();
    auto [sizeX, sizeY] = entity->getComponent<SizeComponent>()->getSize();
    auto [sizeRectX, sizeRectY] = entity->getComponent<SizeRectComponent>()->getSize();

    sprintf(details, "%s %s %s speed %d damage %d position %d %d size %f %f rect %f %f\n",
            entityName[0].c_str(),
            entityName[1].c_str(),
            entityName[2].c_str(),
            speed,
            damage,
            entityX,
            entityY,
            sizeX,
            sizeY,
            sizeRectX,
            sizeRectY);
    sendMessage(MessageType::BULLET_PLAYER, details);
    addMessageClients(std::stoi(entityName[1]), MessageType::BULLET_PLAYER, details);
}
