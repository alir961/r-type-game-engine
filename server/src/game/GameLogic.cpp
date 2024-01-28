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
    createStaticEntity(0, 1420, 420);
    createStaticEntity(1, 420, 024);
    createStaticEntity(2, 666, 666);
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
            move(Direction::RIGHT, entity);
            sendBulletPlayerDetails(entity);
            checkEntitiesStatus();
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

void RType::GameLogic::checkEntitySessions(RType::EntityPtr entity) {
    for (auto &session : _sessionManager.getSessions()) {
        if (session.second != nullptr && session.second->getEntity() == entity)
            session.second->setPlayerEntity(nullptr);
    }
}

void RType::GameLogic::checkEntitiesStatus() {
    auto entities = getEntityManager().getEntities();
    std::vector<EntityPtr> toDestroy;

    for (auto &entity: entities) {
        if (entity->getDeathStatus()) {
            checkEntitySessions(entity);
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
    if (entityName[0] == "static")
        sendStaticEntityDetails(entity);
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
    int startY = rand() % (static_cast<int>(_sessionManager.getWindowHeight()) - 34);
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
    auto [entityX, entityY] = entity->getComponent<PositionComponent>()->getPosition();
    auto [sizeX, sizeY] = entity->getComponent<SizeComponent>()->getSize();
    auto [sizeRectX, sizeRectY] = entity->getComponent<SizeRectComponent>()->getSize();

    sprintf(details, "monster %s speed %d health %d position %.1f %.1f size %.1f %.1f rect %.1f %.1f\n",
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
            auto [currentX, currentY] = entity->getComponent<PositionComponent>()->getPosition();
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
            move(moveDirection, entity);
            sendMonsterDetails(entity);
            checkEntitiesStatus();
        }
    }
}

void RType::GameLogic::sendStaticEntityDetails(const RType::EntityPtr &entity) {
    char details[250];
    std::vector<std::string> entityName = Split::split(entity->getEntityName(), " ");
    auto [entityX, entityY] = entity->getComponent<PositionComponent>()->getPosition();
    auto [sizeX, sizeY] = entity->getComponent<SizeComponent>()->getSize();
    auto [sizeRectX, sizeRectY] = entity->getComponent<SizeRectComponent>()->getSize();

    sprintf(details, "static %s position %.1f %.1f size %.1f %.1f rect %.1f %.1f\n",
            entityName[1].c_str(),
            entityX,
            entityY,
            sizeX,
            sizeY,
            sizeRectX,
            sizeRectY);
    addMessageClients(-1, MessageType::STATIC, details);
}

void RType::GameLogic::createStaticEntity(int staticID, float startX, float startY) {
    EntityPtr staticEntity = getFactory().createStatic(startX, startY);
    char buffer[50];

    sprintf(buffer, "static %d\n", staticID);
    staticEntity->setEntityName(buffer);
    sendStaticEntityDetails(staticEntity);
}

bool RType::GameLogic::move(RType::Direction direction, EntityPtr entity) {
    switch (direction) {
        case Direction::LEFT:
            moveLeft(entity);
            break;
        case Direction::RIGHT:
            moveRight(entity);
            break;
        case Direction::DOWN:
            moveDown(entity);
            break;
        case Direction::UP:
            moveUp(entity);
            break;
    }
    return false;
}

void RType::GameLogic::moveLeft(EntityPtr entity) {
    auto speed = static_cast<float>(entity->getComponent<SpeedComponent>()->getSpeed());
    const auto &[x, y] = entity->getComponent<PositionComponent>()->getPosition();

    if (x - speed < 0)
        entity->setDeathStatus();
    checkHits(entity);
    entity->getComponent<PositionComponent>()->setPositions(std::make_pair(x - speed, y));
}

void RType::GameLogic::moveRight(RType::EntityPtr entity) {
    auto speed = static_cast<float>(entity->getComponent<SpeedComponent>()->getSpeed());
    const auto &[x, y] = entity->getComponent<PositionComponent>()->getPosition();
    float size = entity->getComponent<SizeComponent>()->getSize().second;
    float rect = entity->getComponent<SizeRectComponent>()->getSize().second;
    float entitySize = size * rect;
    float entityX = x + entitySize;

    if (entityX + speed > _sessionManager.getWindowWidth())
        entity->setDeathStatus();
    checkHits(entity);
    entity->getComponent<PositionComponent>()->setPositions(std::make_pair(x + speed, y));
}

void RType::GameLogic::moveDown(RType::EntityPtr entity) {
    auto speed = entity->getComponent<SpeedComponent>()->getSpeed();
    auto [x, y] = entity->getComponent<PositionComponent>()->getPosition();
    float size = entity->getComponent<SizeComponent>()->getSize().second;
    float rect = entity->getComponent<SizeRectComponent>()->getSize().second;
    float entitySize = size * rect;
    float entityY = y + entitySize;

    if (entityY + speed > _sessionManager.getWindowHeight())
        entity->setDeathStatus();
    checkHits(entity);
    entity->getComponent<PositionComponent>()->setPositions(std::make_pair(x, y + speed));
}

void RType::GameLogic::moveUp(RType::EntityPtr entity) {
    auto speed = static_cast<float>(entity->getComponent<SpeedComponent>()->getSpeed());
    const auto &[x, y] = entity->getComponent<PositionComponent>()->getPosition();

    if (y - speed < 0)
        entity->setDeathStatus();
    checkHits(entity);
    entity->getComponent<PositionComponent>()->setPositions(std::make_pair(x, y - speed));
}

void RType::GameLogic::checkHits(RType::EntityPtr entityPtr) {
    for (const auto& entity : _entityManager.getEntities()) {
        if (hit(entityPtr, entity)) {
            if (entity->hasDamageComponent()) {
                setDamageEntity(entityPtr, entity);
                entity->setDeathStatus();
            } else {
                entityPtr->setDeathStatus();
                entity->setDeathStatus();
            }
        }
    }
}

bool RType::GameLogic::hit(RType::EntityPtr entityPtr, EntityPtr entity) {
    const auto& [thisX, thisY] = entityPtr->getComponent<PositionComponent>()->getPosition();
    const auto& [thisWidth, thisHeight] = entityPtr->getComponent<SizeComponent>()->getSize();
    const auto& [thisRectWidth, thisRectHeight] = entityPtr->getComponent<SizeRectComponent>()->getSize();
    float thisActualWidth = thisWidth * thisRectWidth;
    float thisActualHeight = thisHeight * thisRectHeight;
    const auto& [entityX, entityY] = entity->getComponent<PositionComponent>()->getPosition();
    const auto& [entityWidth, entityHeight] = entity->getComponent<SizeComponent>()->getSize();
    const auto& [entityRectWidth, entityRectHeight] = entity->getComponent<SizeRectComponent>()->getSize();
    float entityActualWidth = entityWidth * entityRectWidth;
    float entityActualHeight = entityHeight * entityRectHeight;

    if (entityPtr == entity) {
        return false;
    }
    return (thisX < entityX + entityActualWidth &&
            thisX + thisActualWidth > entityX &&
            thisY < entityY + entityActualHeight &&
            thisY + thisActualHeight > entityY);
}

void RType::GameLogic::setDamageEntity(RType::EntityPtr entityPtr, RType::EntityPtr entity) {
    if (entityPtr->hasHealthComponent())
        putDamage(entityPtr, entity);
    else
        entityPtr->setDeathStatus();
}

void RType::GameLogic::putDamage(RType::EntityPtr entityPtr, RType::EntityPtr entity) {
    auto healthComponent = entityPtr->getComponent<HealthComponent>();
    int health = healthComponent->getHealth();
    int damage = entity->getComponent<DamageComponent>().get()->getDamage();
    auto player = getPlayerEntity(std::stoi(Split::split(entity->getEntityName(), " \n")[1]));


    if (health - damage <= 0)
        entityPtr->setDeathStatus();
    else
        healthComponent->setHealth(health - damage);
    if (player == nullptr)
        return;
    auto playerComponent = player->getComponent<PlayerComponent>();
    playerComponent->setScore(playerComponent->getScore() + damage);
}

RType::EntityPtr RType::GameLogic::getPlayerEntity(int playerID) {
    for (const auto& entity : _entityManager.getEntities()) {
        std::vector<std::string> entityName = Split::split(entity->getEntityName(), " \n");
        if (playerID == std::stoi(entityName[1]) && entity->hasPlayerComponent())
            return entity;
    }
    return nullptr;
}

