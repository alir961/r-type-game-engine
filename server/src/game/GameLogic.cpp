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
    if (_tickNumber % (5 * TICK_PER_SECOND) == 0)
        createMonsterEntity();
    movePlayerBullets();
    moveMonsters();
    serverLoopIterate();
}


bool RType::GameLogic::isStopped() {
    if (_stop)
        _thread.wait();
    return _stop;
}

void RType::GameLogic::movePlayerBullets() {
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
    auto [playerX, playerY] = player->getComponent<PositionComponent>()->getPosition();
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
    if (entityName[0] == "monster")
        sendMonsterDetails(entity);
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
    auto [playerX, playerY] = entity->getComponent<PositionComponent>()->getPosition();
    auto [sizeX, sizeY] = entity->getComponent<SizeComponent>()->getSize();
    auto [sizeRectX, sizeRectY] = entity->getComponent<SizeRectComponent>()->getSize();
    std::string playerName = entity->getComponent<PlayerComponent>()->getUsername();
    int score = entity->getComponent<PlayerComponent>()->getScore();

    sprintf(details, "player %s speed %d health %d position %.1f %.1f size %.1f %.1f rect %.1f %.1f color %s name %s score %d\n",
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
    auto [entityX, entityY] = entity->getComponent<PositionComponent>()->getPosition();
    auto [sizeX, sizeY] = entity->getComponent<SizeComponent>()->getSize();
    auto [sizeRectX, sizeRectY] = entity->getComponent<SizeRectComponent>()->getSize();

    sprintf(details, "%s %s %s speed %d damage %d position %.1f %.1f size %.1f %.1f rect %.1f %.1f\n",
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
void RType::GameLogic::createMonsterEntity() {
    float startX = _sessionManager.getWindowWidth();
    int startY = rand() % (static_cast<int>(_sessionManager.getWindowWidth()) - 32);
    EntityPtr monsterEntity = getFactory().createMonster(startX, static_cast<float>(startY));
    char buffer[50];

    sprintf(buffer, "monster %d\n", getNextMonsterID());
    monsterEntity->setEntityName(buffer);
    sendMonsterDetails(monsterEntity);
}

int RType::GameLogic::getNextMonsterID() {
    if (_lastMonsterID == 100)
        _lastMonsterID = 0;
    return (_lastMonsterID++);
}

void RType::GameLogic::sendMonsterDetails(const RType::EntityPtr &entity) {
    char details[250];
    std::vector<std::string> entityName = Split::split(entity->getEntityName(), " ");
    int speed = entity->getComponent<SpeedComponent>()->getSpeed();
    int health = entity->getComponent<HealthComponent>()->getHealth();
    auto [entityX, entityY] = entity->getComponent<PositionComponent>()->getPositions();
    auto [sizeX, sizeY] = entity->getComponent<SizeComponent>()->getSize();
    auto [sizeRectX, sizeRectY] = entity->getComponent<SizeRectComponent>()->getSize();

    sprintf(details, "monster %s speed %d health %d position %d %d dsize %f %f rect %f %f\n",
            entityName[1].c_str(),
            speed,
            health,
            entityX,
            entityY,
            sizeX,
            sizeY,
            sizeRectX,
            sizeRectY);
    addMessageClients(-1, MessageType::MONSTER, details);
}

void RType::GameLogic::moveMonsters() {
    for (auto &entity: _entityManager.getEntities()) {
        if (Split::split(entity->getEntityName(), " ")[0] == "monster") {
            auto [currentX, currentY] = entity->getComponent<PositionComponent>()->getPositions();
            Direction moveDirection;
            int randomDirection = rand() % 3;

            if (randomDirection == 0)
                moveDirection = Direction::LEFT;
            else if (randomDirection == 1)
                moveDirection = Direction::UP;
            else
                moveDirection = Direction::DOWN;
            if ((moveDirection == Direction::UP && currentY <= 0) ||
                (moveDirection == Direction::DOWN && currentY >= _sessionManager.getWindowHeight() - 32)) {
                moveDirection = Direction::LEFT;
            }
            entity->move(moveDirection, _entityManager.getEntities(), _sessionManager.getWindowWidth(),
                         _sessionManager.getWindowHeight());
            sendMonsterDetails(entity);
            checkEntitiesStatus(nullptr);
        }
    }
}
