/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.cpp
*/

#include "../include/ClientViewport.hpp"
#include "engine/modules/animation/IAnimationModule.hpp"

RType::ClientViewport::ClientViewport() {
    _graphicalModule = _provider->loadAndGetModule<RType::IGraphicalModule>(RType::ModuleType::GRAPHICAL);
    _animationModule = _provider->loadAndGetModule<RType::IAnimationModule>(RType::ModuleType::ANIMATION);
    _graphicalModule->openWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "R-Type");
    _selectedView = std::make_shared<LoginView>(*this);
    setHandlers();
}

void RType::ClientViewport::handleInput() const {
    char buffer[100];

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprintf(buffer, "move_right %d\n", _client->getClientID());
        _client->sendMessage(MessageType::MOVE_RIGHT, buffer);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprintf(buffer, "move_left %d\n", _client->getClientID());
        _client->sendMessage(MessageType::MOVE_LEFT, buffer);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        sprintf(buffer, "move_up %d\n", _client->getClientID());
        _client->sendMessage(MessageType::MOVE_UP, buffer);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        sprintf(buffer, "move_down %d\n", _client->getClientID());
        _client->sendMessage(MessageType::MOVE_DOWN, buffer);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        sprintf(buffer, "color %d\n", _client->getClientID());
        _client->sendMessage(MessageType::PLAYER_COLOR, buffer);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        sprintf(buffer, "bulletPlayer %d\n", _client->getClientID());
        _client->sendMessage(MessageType::SHOOT, buffer);
    }
}

void RType::ClientViewport::basicInput() {
    if (_viewState == ViewState::OPTIONS) {
        if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::BackSpace) {
            _logger->debug("Return key pressed in OPTIONS state");
            setView(ViewState::MENU);
        }
    } else if (_viewState == ViewState::GAME) {
        if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape) {
            _logger->debug("Return key pressed in GAME state");
            setView(ViewState::PAUSE);
        }
    } else if (_viewState == ViewState::PAUSE) {
        if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape) {
            _logger->debug("Return key pressed in PAUSE state");
            setView(ViewState::GAME);
        }
    } else if (_viewState == ViewState::WIN || _viewState == ViewState::DEAD) {
        if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape) {
            setView(ViewState::MENU);
        }
    }
}

void RType::ClientViewport::launchWindow() {
    const float fixedTimeStep = 1.F / WINDOW_FPS;
    float accumulatedTime = 0.F;

    while (_graphicalModule->isOpen()) {
        while (_graphicalModule->pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                _graphicalModule->close();
                closeConnectionToServer();
                return;
            }
            basicInput();
        }
        if (_viewState == ViewState::GAME) {
            char buffer[100];
            handleMessageFromServer();
            handleInput();
            sprintf(buffer, "tick %d\n", _client->getClientID());
            _client->sendMessage(MessageType::TICK, buffer);
        }
        _selectedView->update();
        accumulatedTime += _animationClock.restart().asSeconds();
        while (accumulatedTime >= fixedTimeStep) {
            updateEntities(fixedTimeStep);
            accumulatedTime -= fixedTimeStep;
        }
        draw();
    }
    _logger->info("Exit game");
}

void RType::ClientViewport::setView(ViewState state) {
    EntityPtr player;
    switch (state) {
        case ViewState::MENU:
            _selectedView = std::make_shared<MenuView>(*this);
            break;
        case ViewState::OPTIONS:
            _selectedView = std::make_shared<OptionsView>(*this);
            break;
        case ViewState::OPTIONSGAME:
            _selectedView = std::make_shared<OptionsView>(*this, true);
            break;
        case ViewState::GAME:
            char buffer[50];

            _selectedView = std::make_shared<GameView>(_client->getUsername());
            sprintf(buffer, "player %d %s\n", _client->getClientID(), _client->getUsername().c_str());
            _client->sendMessage(MessageType::PLAYER_NAME, buffer);
            break;
        case ViewState::PAUSE:
            _selectedView = std::make_shared<PauseView>(*this);
            break;
        case ViewState::LOGIN:
            _selectedView = std::make_shared<LoginView>(*this);
            break;
        case ViewState::LOADSCREEN:
            _selectedView = std::make_shared<LoadView>(*this, _client);
            break;
    }
    _selectedView->setPlayerEntity(_playerEntity);
    _viewState = state;
}

void RType::ClientViewport::addGraphicEntity(const GraphicEntityPtr &entity) {
    _graphicEntities.push_back(entity);
    _logger->debug("Entity registered: " + entity->getEntityName());
}

RType::GraphicEntityPtr RType::ClientViewport::getGraphicEntityByName(const std::string &name) const {
    for (const auto &entity: _graphicEntities) {
        if (entity->getEntity()->getEntityName() == name)
            return entity;
    }
    return nullptr;
}

sf::Event RType::ClientViewport::getEvent() const {
    return _event;
}

void RType::ClientViewport::connectToServer(const std::string &hostname, int port, std::string username) {
    _logger->warn("Connection attempt to server " + hostname + ":" + std::to_string(port));
    _client = std::make_shared<RType::UDPClient>(hostname, port, username, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void RType::ClientViewport::closeConnectionToServer() {
    _client = nullptr;
}

void RType::ClientViewport::updateEntities(float deltaTime) {
    for (const auto &entity: _graphicEntities) {
        entity->update(deltaTime, _animationModule);
        _selectedView->update();
    }
}

void RType::ClientViewport::draw() {
    _graphicalModule->clear();
    _selectedView->draw(_graphicEntities);
    _graphicalModule->display();
}

int RType::ClientViewport::start() {
    try {
        _logger->info("Launching application [...]");
        launchWindow();
    } catch (const std::exception &e) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void RType::ClientViewport::handleMessageFromServer() {
    auto handleMessage = [this](const std::string &message) {
        std::vector<std::string> splitMessage;

        if (message.empty()) return;
        splitMessage = Split::split(message, " \n");

        if (_handlers.contains(splitMessage[0]))
            _handlers[splitMessage[0]](splitMessage);
        else _logger->error("No handler found for message type: " + splitMessage[0]);
    };

    for (const auto &message: _client->pullQueue())
        handleMessage(message);
}

void RType::ClientViewport::setHandlers() {
    _handlers["player"] = [this](const std::vector<std::string> &splitMessage) { player(splitMessage); };
    _handlers["color"] = [this](const std::vector<std::string> &splitMessage) { changePlayerColor(splitMessage); };
    _handlers["bulletPlayer"] = [this](const std::vector<std::string> &splitMessage) { bulletPlayer(splitMessage); };
    _handlers["death"] = [this](const std::vector<std::string> &splitMessage) { death(splitMessage); };
    _handlers["disconnect"] = [this](const std::vector<std::string> &splitMessage) { disconnect(splitMessage); };
}

void RType::ClientViewport::changePlayerColor(const std::vector<std::string> &splitMessage) {
    int sessionID = std::stoi(splitMessage[1]);
    std::string color = splitMessage[2];

    char buffer[100];
    sprintf(buffer, "%sPlayer %d", color.c_str(), sessionID);
    _playerEntity->getEntity()->setEntityName(buffer);
}

void RType::ClientViewport::death(const std::vector<std::string> &splitMessage) {
    int index = 0;
    std::string entityName = splitMessage[1];
    EntityPtr entity;
    GraphicEntityPtr graphicEntity;

    for (auto &split: splitMessage) {
        if (index != 0 && index != 1)
            entityName += " " + split;
        index++;
    }
    graphicEntity = getGraphicEntityByName(entityName);
    if (graphicEntity == nullptr) return;
    entity = graphicEntity->getEntity();
    if (_playerEntity == nullptr) {
        setView(ViewState::MENU);
        return;
    }
    if (entityName == _playerEntity->getEntity()->getEntityName()) {
        _client->setHealth(_playerEntity->getEntity()->getComponent<HealthComponent>()->getHealth());
        _client->setScore(_playerEntity->getEntity()->getComponent<PlayerComponent>()->getScore());
        setView(ViewState::MENU);
    }
    destroyGraphicEntity(graphicEntity);
    _entityManager.destroyEntity(entity);
    char buffer[100];
    std::sprintf(buffer, "death %s", entityName.c_str());
    std::cout << buffer << "\n";
}

void RType::ClientViewport::destroyGraphicEntity(RType::GraphicEntityPtr entity) {
    auto it = std::find(_graphicEntities.begin(), _graphicEntities.end(), entity);

    if (it != _graphicEntities.end())
        _graphicEntities.erase(it);
}

void RType::ClientViewport::player(const std::vector<std::string> &splitMessage) {
    int sessionID = std::stoi(splitMessage[1]);
    std::string color = splitMessage[16];
    GraphicEntityPtr entity = getGraphicEntityByName(color + " " + std::to_string(sessionID));

    if (entity == nullptr)
        createNewPlayer(splitMessage);
    else
        updatePlayer(splitMessage);
}

void RType::ClientViewport::bulletPlayer(const std::vector<std::string> &splitMessage) {
    int sessionID = std::stoi(splitMessage[1]);
    int bulletID = std::stoi(splitMessage[2]);
    std::string entityName = splitMessage[0];
    GraphicEntityPtr entity = getGraphicEntityByName(entityName + " " + std::to_string(sessionID) + " " + std::to_string(bulletID));

    if (entity == nullptr)
        createNewBulletPlayer(splitMessage);
    else
        updateBulletPlayer(splitMessage);
}

void RType::ClientViewport::createNewPlayer(const std::vector<std::string> &splitMessage) {
    int sessionID = std::stoi(splitMessage[1]);
    int speed = std::stoi(splitMessage[3]);
    int health = std::stoi(splitMessage[5]);
    int positionX = std::stoi(splitMessage[7]);
    int positionY = std::stoi(splitMessage[8]);
    float sizeX = std::stof(splitMessage[10]);
    float sizeY = std::stof(splitMessage[11]);
    float rectX = std::stof(splitMessage[13]);
    float rectY = std::stof(splitMessage[14]);
    std::string color = splitMessage[16];
    std::string name = splitMessage[18];
    int score = std::stoi(splitMessage[20]);
    auto starshipEntity = _entityManager.createEntity();
    //std::shared_ptr<RType::GraphicEntity> graphicStarship;


    starshipEntity->addComponent<RType::SpeedComponent>(speed);
    starshipEntity->addComponent<RType::HealthComponent>(health);
    starshipEntity->addComponent<RType::PositionComponent>(std::make_pair(positionX, positionY));
    starshipEntity->addComponent<RType::SizeComponent>(sizeX, sizeY);
    starshipEntity->addComponent<RType::SizeRectComponent>(rectX, rectY);
    starshipEntity->addComponent<RType::PlayerComponent>(true);
    starshipEntity->getComponent<RType::PlayerComponent>()->setUserName(name);
    starshipEntity->getComponent<RType::PlayerComponent>()->setScore(score);
    starshipEntity->setEntityName(color + " " + std::to_string(sessionID));
    /*if (starshipEntity->hasBaseComponents()) {
        graphicStarship = GraphicEntityFactory::createGraphicEntity(starshipEntity,"client/assets/sprites/r-typesheet42.gif", color);
        graphicStarship->loadSprite(_animationModule);
        if (sessionID == _client->getClientID()) {
            _playerEntity = graphicStarship;
            _selectedView->setPlayerEntity(graphicStarship);
            _client->setHealth(starshipEntity->getComponent<HealthComponent>()->getHealth());
            _client->setScore(starshipEntity->getComponent<PlayerComponent>()->getScore());
        }
        addGraphicEntity(graphicStarship);
    }*/
}

void RType::ClientViewport::updatePlayer(const std::vector<std::string> &splitMessage) {
    int sessionID = std::stoi(splitMessage[1]);
    int speed = std::stoi(splitMessage[3]);
    int health = std::stoi(splitMessage[5]);
    int positionX = std::stoi(splitMessage[7]);
    int positionY = std::stoi(splitMessage[8]);
    float sizeX = std::stof(splitMessage[10]);
    float sizeY = std::stof(splitMessage[11]);
    float rectX = std::stof(splitMessage[13]);
    float rectY = std::stof(splitMessage[14]);
    std::string color = splitMessage[16];
    std::string name = splitMessage[18];
    int score = std::stoi(splitMessage[20]);
    EntityPtr starshipEntity = getGraphicEntityByName(color + " " + std::to_string(sessionID))->getEntity();

    starshipEntity->getComponent<RType::SpeedComponent>()->setSpeed(speed);
    starshipEntity->getComponent<RType::HealthComponent>()->setHealth(health);
    starshipEntity->getComponent<RType::PositionComponent>()->setPositions(std::make_pair(positionX, positionY));
    starshipEntity->getComponent<RType::SizeComponent>()->setSize(sizeX, sizeY);
    starshipEntity->getComponent<RType::SizeRectComponent>()->setSize(rectX, rectY);
    starshipEntity->getComponent<RType::PlayerComponent>()->setUserName(name);
    starshipEntity->getComponent<RType::PlayerComponent>()->setScore(score);
}

void RType::ClientViewport::updateBulletPlayer(const std::vector<std::string> &splitMessage) {
    int sessionID = std::stoi(splitMessage[1]);
    int bulletID = std::stoi(splitMessage[2]);
    int speed = std::stoi(splitMessage[4]);
    int damage = std::stoi(splitMessage[6]);
    int positionX = std::stoi(splitMessage[8]);
    int positionY = std::stoi(splitMessage[9]);
    float sizeX = std::stof(splitMessage[11]);
    float sizeY = std::stof(splitMessage[12]);
    float rectX = std::stof(splitMessage[14]);
    float rectY = std::stof(splitMessage[15]);
    char entityName[250];
    EntityPtr bulletEntity;

    sprintf(entityName, "bulletPlayer %d %d", sessionID, bulletID);
    bulletEntity = getGraphicEntityByName(entityName)->getEntity();

    bulletEntity->getComponent<RType::SpeedComponent>()->setSpeed(speed);
    bulletEntity->getComponent<RType::DamageComponent>()->setDamage(damage);
    bulletEntity->getComponent<RType::PositionComponent>()->setPositions(std::make_pair(positionX, positionY));
    bulletEntity->getComponent<RType::SizeComponent>()->setSize(sizeX, sizeY);
    bulletEntity->getComponent<RType::SizeRectComponent>()->setSize(rectX, rectY);
}

void RType::ClientViewport::createNewBulletPlayer(const std::vector<std::string> &splitMessage) {
    auto bulletEntity = _entityManager.createEntity();
    std::shared_ptr<RType::GraphicEntity> graphicBullet;
    int sessionID = std::stoi(splitMessage[1]);
    int bulletID = std::stoi(splitMessage[2]);
    int speed = std::stoi(splitMessage[4]);
    int damage = std::stoi(splitMessage[6]);
    int positionX = std::stoi(splitMessage[8]);
    int positionY = std::stoi(splitMessage[9]);
    float sizeX = std::stof(splitMessage[11]);
    float sizeY = std::stof(splitMessage[12]);
    float rectX = std::stof(splitMessage[14]);
    float rectY = std::stof(splitMessage[15]);
    char entityName[250];

    bulletEntity->addComponent<RType::SpeedComponent>(speed);
    bulletEntity->addComponent<RType::DamageComponent>(damage);
    bulletEntity->addComponent<RType::PositionComponent>(std::make_pair(positionX, positionY));
    bulletEntity->addComponent<RType::SizeComponent>(sizeX, sizeY);
    bulletEntity->addComponent<RType::SizeRectComponent>(rectX, rectY);
    bulletEntity->addComponent<RType::PlayerComponent>(false);
    sprintf(entityName, "bulletPlayer %d %d", sessionID, bulletID);
    bulletEntity->setEntityName(entityName);
    graphicBullet = GraphicEntityFactory::createGraphicEntity(bulletEntity, "client/assets/sprites/r-typesheet2.gif", "bulletPlayer");
    addGraphicEntity(graphicBullet);
    graphicBullet->loadSprite(_animationModule);
}

void RType::ClientViewport::disconnect(const std::vector<std::string> &splitMessage) {
    if (splitMessage.size() == 1) return;
    std::string entityName = splitMessage[1] + " " + splitMessage[2];
    GraphicEntityPtr graphicEntity = getGraphicEntityByName(entityName);
    EntityPtr entity;

    if (graphicEntity == nullptr) return;
    entity = graphicEntity->getEntity();
    destroyGraphicEntity(graphicEntity);
    _entityManager.destroyEntity(entity);
    char buffer[100];
    std::sprintf(buffer, "disconnect %s", entityName.c_str());
    std::cout << buffer << "\n";
}
