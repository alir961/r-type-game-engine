/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#include <algorithm>
#include <array>
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
    createStaticEntity(0, 1420, 950);
    createStaticEntity(1, 420, 420);
    createStaticEntity(2, 666, 24);
    _thread.run([this]() { serverLoop(); });
}

void RType::GameLogic::serverLoop() {
    auto nextTick = std::chrono::steady_clock::now();

    // A fixed-rate loop: the old recursive version grew the stack every tick and drifted
    // by the time spent simulating.
    while (!_stop) {
        nextTick += std::chrono::milliseconds(EPSILON_TIME_MS);
        serverLoopIterate();
        std::this_thread::sleep_until(nextTick);
    }
}

void RType::GameLogic::serverLoopIterate() {
    const auto guard = lock();

    const DifficultySettings &settings = getDifficultySettings(_difficulty);
    const auto ticks = [](float seconds) { return static_cast<int>(seconds * TICK_PER_SECOND); };

    _tickNumber++;
    if (--_ticksUntilMonster <= 0) {
        createMonsterEntity();
        _ticksUntilMonster = ticks(settings.monsterEverySeconds);
    }
    if (--_ticksUntilStarship <= 0) {
        createStarshipEntity();
        _ticksUntilStarship = ticks(settings.starshipEverySeconds);
    }
    if (--_ticksUntilVolley <= 0) {
        _ticksUntilVolley = ticks(settings.starshipFireEverySeconds);
        for (auto &entity: _entityManager.getEntities()) {
            if (Split::split(entity->getEntityName(), " \n")[0] == "starship") {
                createBulletStarshipEntity(entity);
            }
        }
    }
    movePlayerBullets();
    moveStarshipsBullets();
    moveMonsters();
    moveStarships();
    flushAllClients();
}

void RType::GameLogic::setDifficulty(RType::Difficulty difficulty) {
    const DifficultySettings &settings = getDifficultySettings(difficulty);
    char buffer[50];

    _difficulty = difficulty;
    _ticksUntilMonster = std::min(_ticksUntilMonster, static_cast<int>(settings.monsterEverySeconds * TICK_PER_SECOND));
    _ticksUntilStarship = std::min(_ticksUntilStarship, static_cast<int>(settings.starshipEverySeconds * TICK_PER_SECOND));
    _ticksUntilVolley = std::min(_ticksUntilVolley, static_cast<int>(settings.starshipFireEverySeconds * TICK_PER_SECOND));
    sprintf(buffer, "difficulty %s\n", difficultyToString(difficulty).c_str());
    addMessageClients(-1, MessageType::DIFFICULTY, buffer);
    std::cout << "Difficulty set to " << difficultyToString(difficulty) << "\n";
}

void RType::GameLogic::flushAllClients() {
    for (const auto &[sessionID, client]: _sessionManager.getSessions()) {
        if (client == nullptr)
            continue;
        for (const Message &message: client->takeMessages())
            _adapter->sendTo(message, client->getEndpoint());
    }
}

void RType::GameLogic::sendTo(int sessionID, RType::MessageType type, const std::string_view &data) {
    const Session client = _sessionManager.getClientSession(sessionID);

    if (client != nullptr)
        _adapter->sendTo(NetworkMessageBuilder(type).setData(data).build(), client->getEndpoint());
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
        }
    }
    checkEntitiesStatus();
}

void RType::GameLogic::sendMessage(RType::MessageType type, const std::string_view &data) {
    // Queued for every player and sent at the end of the tick, each to its own address.
    addMessageClients(-1, type, data);
}

RType::EntityPtr RType::GameLogic::createPlayerEntity(int sessionID, const RType::Session &session) {
    // One lane per player, clear of the mines, so co-op players don't spawn inside each other.
    constexpr std::array<float, 4> SPAWN_Y = {650.0f, 800.0f, 300.0f, 180.0f};
    EntityPtr playerEntity = getFactory().createDefaultPlayer(session->getPlayerName());
    char buffer[50];

    playerEntity->getComponent<PositionComponent>()->setPositions(std::make_pair(150.0f, SPAWN_Y[sessionID % SPAWN_Y.size()]));

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
    float playerSizeY = player->getComponent<SizeComponent>()->getSize().second;
    float playerRectY = player->getComponent<SizeRectComponent>()->getSize().second;
    float startX = playerX + (playerRectX * playerSizeX);
    EntityPtr bulletEntity;
    char bulletName[200];

    bulletEntity = getFactory().createBulletPlayer(startX, playerY);
    // Center the shot on the ship's nose.
    float bulletHeight = bulletEntity->getComponent<SizeComponent>()->getSize().second *
                         bulletEntity->getComponent<SizeRectComponent>()->getSize().second;
    bulletEntity->getComponent<PositionComponent>()->setPositions(
            std::make_pair(startX, playerY + (playerRectY * playerSizeY - bulletHeight) / 2.0f));
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

    if (client == nullptr)
        return;
    for (const Message &message: client->takeMessages())
        _adapter->sendTo(message, client->getEndpoint());
}

void RType::GameLogic::sendAllEntities(int sessionID) {
    Session client = _sessionManager.getClientSession(sessionID);

    char buffer[50];

    for (auto &entity : getEntityManager().getEntities())
        sendMessageFromEntity(entity);
    sprintf(buffer, "difficulty %s\n", difficultyToString(_difficulty).c_str());
    if (client != nullptr)
        client->addMessage(NetworkMessageBuilder(MessageType::DIFFICULTY).setData(buffer).build());
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
}
void RType::GameLogic::createMonsterEntity() {
    float startX = _sessionManager.getWindowWidth();
    const DifficultySettings &settings = getDifficultySettings(_difficulty);
    EntityPtr monsterEntity = getFactory().createMonster(startX, 0.0f);

    monsterEntity->getComponent<HealthComponent>()->setHealth(settings.monsterHealth);
    monsterEntity->getComponent<SpeedComponent>()->setSpeed(settings.monsterSpeed);
    float monsterHeight = monsterEntity->getComponent<SizeComponent>()->getSize().second *
                          monsterEntity->getComponent<SizeRectComponent>()->getSize().second;
    int startY = rand() % (static_cast<int>(_sessionManager.getWindowHeight() - monsterHeight) - 2) + 1;

    monsterEntity->getComponent<PositionComponent>()->setPositions(std::make_pair(startX, static_cast<float>(startY)));
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
            float speed = static_cast<float>(entity->getComponent<SpeedComponent>()->getSpeed());
            float height = entity->getComponent<SizeComponent>()->getSize().second *
                           entity->getComponent<SizeRectComponent>()->getSize().second;
            Direction moveDirection;
            int randomDirection = rand() % 3;

            if (randomDirection == 0)
                moveDirection = Direction::LEFT;
            else if (randomDirection == 1)
                moveDirection = Direction::UP;
            else
                moveDirection = Direction::DOWN;
            // Leaving the screen kills an entity: turn left instead of crossing the top or bottom edge.
            if ((moveDirection == Direction::UP && currentY - speed < 0) ||
                (moveDirection == Direction::DOWN && currentY + height + speed > _sessionManager.getWindowHeight())) {
                moveDirection = Direction::LEFT;
            }
            move(moveDirection, entity);
            sendMonsterDetails(entity);
        }
    }
    checkEntitiesStatus();
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

void RType::GameLogic::movePlayer(RType::Direction direction, EntityPtr entity) {
    auto speed = static_cast<float>(entity->getComponent<SpeedComponent>()->getSpeed());
    const auto [x, y] = entity->getComponent<PositionComponent>()->getPosition();
    const auto [sizeX, sizeY] = entity->getComponent<SizeComponent>()->getSize();
    const auto [rectX, rectY] = entity->getComponent<SizeRectComponent>()->getSize();
    const float maxX = std::max(0.0f, _sessionManager.getWindowWidth() - sizeX * rectX);
    const float maxY = std::max(0.0f, _sessionManager.getWindowHeight() - sizeY * rectY);
    float newX = x;
    float newY = y;

    switch (direction) {
        case Direction::LEFT:
            newX -= speed;
            break;
        case Direction::RIGHT:
            newX += speed;
            break;
        case Direction::DOWN:
            newY += speed;
            break;
        case Direction::UP:
            newY -= speed;
            break;
    }
    checkHits(entity);
    entity->getComponent<PositionComponent>()->setPositions(
            std::make_pair(std::clamp(newX, 0.0f, maxX), std::clamp(newY, 0.0f, maxY)));
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

namespace {
    /**
     * Players, and players' shots, are on the same side: they pass through each other.
     */
    bool isFriendly(const std::string &name) {
        const std::string type = name.substr(0, name.find(' '));

        return type == "bulletPlayer" || (type.ends_with("Player") && type != "bulletPlayer");
    }
}

void RType::GameLogic::checkHits(RType::EntityPtr entityPtr) {
    const bool friendly = isFriendly(entityPtr->getEntityName());

    for (const auto& entity : _entityManager.getEntities()) {
        if (friendly && isFriendly(entity->getEntityName()))
            continue;
        if (hit(entityPtr, entity)) {
            if (entity->hasDamageComponent()) {
                setDamageEntity(entityPtr, entity);
                entity->setDeathStatus();
            } else if (entityPtr->hasDamageComponent()) {
                setDamageEntity(entity, entityPtr);
                entityPtr->setDeathStatus();
            } else {
                entity->setDeathStatus();
                entityPtr->setDeathStatus();
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
    else {
        healthComponent->setHealth(health - damage);
        sendMessageFromEntity(entityPtr);
    }
    if (player == nullptr)
        return;
    auto playerComponent = player->getComponent<PlayerComponent>();
    playerComponent->setScore(playerComponent->getScore() + damage);
    sendPlayerDetails(player);
}

RType::EntityPtr RType::GameLogic::getPlayerEntity(int playerID) {
    for (const auto& entity : _entityManager.getEntities()) {
        std::vector<std::string> entityName = Split::split(entity->getEntityName(), " \n");
        if (playerID == std::stoi(entityName[1]) && entity->hasPlayerComponent())
            return entity;
    }
    return nullptr;
}

int RType::GameLogic::getNextStarshipID() {
    return (_lastStarshipID++);
}

int RType::GameLogic::getNextBulletStarshipID(int starshipID) {
    return (_lastBulletStarship[starshipID]++);
}

void RType::GameLogic::createStarshipEntity() {
    float startX = _sessionManager.getWindowWidth();
    const DifficultySettings &settings = getDifficultySettings(_difficulty);
    EntityPtr starshipEntity = getFactory().createStarship(startX, 0.0f);

    starshipEntity->getComponent<HealthComponent>()->setHealth(settings.starshipHealth);
    starshipEntity->getComponent<SpeedComponent>()->setSpeed(settings.starshipSpeed);
    float starshipHeight = starshipEntity->getComponent<SizeComponent>()->getSize().second *
                           starshipEntity->getComponent<SizeRectComponent>()->getSize().second;
    int startY = rand() % (static_cast<int>(_sessionManager.getWindowHeight() - starshipHeight) - 2) + 1;
    char buffer[50];

    starshipEntity->getComponent<PositionComponent>()->setPositions(std::make_pair(startX, static_cast<float>(startY)));

    sprintf(buffer, "starship %d\n", getNextStarshipID());
    starshipEntity->setEntityName(buffer);
    sendStarshipDetails(starshipEntity);
}

void RType::GameLogic::createBulletStarshipEntity(EntityPtr entity) {
    const std::string message;
    if (entity == nullptr) return;
    auto [playerX, playerY] = entity->getComponent<PositionComponent>()->getPosition();
    float shipHeight = entity->getComponent<SizeComponent>()->getSize().second *
                       entity->getComponent<SizeRectComponent>()->getSize().second;
    EntityPtr bulletEntity;
    char bulletName[200];
    int entityID = std::stoi(Split::split(entity->getEntityName(), " \n")[1]);

    bulletEntity = getFactory().createBulletStarship(playerX, playerY);
    bulletEntity->getComponent<DamageComponent>()->setDamage(getDifficultySettings(_difficulty).enemyShotDamage);
    // Fire from the ship's nose, centered vertically.
    auto [bulletSizeX, bulletSizeY] = bulletEntity->getComponent<SizeComponent>()->getSize();
    auto [bulletRectX, bulletRectY] = bulletEntity->getComponent<SizeRectComponent>()->getSize();
    bulletEntity->getComponent<PositionComponent>()->setPositions(
            std::make_pair(playerX - bulletSizeX * bulletRectX - 4.0f, playerY + (shipHeight - bulletSizeY * bulletRectY) / 2.0f));
    sprintf(bulletName, "bulletStarship %d %d", entityID, getNextBulletStarshipID(entityID));
    bulletEntity->setEntityName(bulletName);
    sendBulletPlayerDetails(bulletEntity);
}

void RType::GameLogic::moveStarships() {
    for (auto &entity: _entityManager.getEntities()) {
        if (Split::split(entity->getEntityName(), " ")[0] == "starship") {
            auto [currentX, currentY] = entity->getComponent<PositionComponent>()->getPosition();
            float speed = static_cast<float>(entity->getComponent<SpeedComponent>()->getSpeed());
            float height = entity->getComponent<SizeComponent>()->getSize().second *
                           entity->getComponent<SizeRectComponent>()->getSize().second;
            Direction moveDirection;
            int randomDirection = rand() % 3;

            if (randomDirection == 0)
                moveDirection = Direction::LEFT;
            else if (randomDirection == 1)
                moveDirection = Direction::UP;
            else
                moveDirection = Direction::DOWN;
            // Leaving the screen kills an entity: turn left instead of crossing the top or bottom edge.
            if ((moveDirection == Direction::UP && currentY - speed < 0) ||
                (moveDirection == Direction::DOWN && currentY + height + speed > _sessionManager.getWindowHeight())) {
                moveDirection = Direction::LEFT;
            }
            move(moveDirection, entity);
            sendStarshipDetails(entity);
        }
    }
    checkEntitiesStatus();
}

void RType::GameLogic::moveStarshipsBullets() {
    for (auto &entity: _entityManager.getEntities()) {
        if (Split::split(entity->getEntityName(), " ")[0] == "bulletStarship") {
            move(Direction::LEFT, entity);
            sendBulletStarshipDetails(entity);
        }
    }
    checkEntitiesStatus();
}

void RType::GameLogic::sendBulletStarshipDetails(const RType::EntityPtr &entity) {
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
    addMessageClients(-1, MessageType::BULLET_STARSHIP, details);
}

void RType::GameLogic::sendStarshipDetails(const RType::EntityPtr &entity) {
    char details[250];
    std::vector<std::string> entityName = Split::split(entity->getEntityName(), " ");
    int speed = entity->getComponent<SpeedComponent>()->getSpeed();
    int health = entity->getComponent<HealthComponent>()->getHealth();
    auto [entityX, entityY] = entity->getComponent<PositionComponent>()->getPosition();
    auto [sizeX, sizeY] = entity->getComponent<SizeComponent>()->getSize();
    auto [sizeRectX, sizeRectY] = entity->getComponent<SizeRectComponent>()->getSize();

    sprintf(details, "starship %s speed %d health %d position %.1f %.1f size %.1f %.1f rect %.1f %.1f\n",
            entityName[1].c_str(),
            speed,
            health,
            entityX,
            entityY,
            sizeX,
            sizeY,
            sizeRectX,
            sizeRectY);
    addMessageClients(-1, MessageType::STARSHIP, details);
}
