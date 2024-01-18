/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.cpp
*/

#include "../include/ClientViewport.hpp"
#include "engine/modules/animation/IAnimationModule.hpp"

RType::ClientViewport::ClientViewport() {
    _window.setFramerateLimit(WINDOW_FPS);
    _graphicalModule = _provider.loadAndGetModule<RType::IGraphicalModule>(RType::ModuleType::GRAPHICAL);
    _animationModule = _provider.loadAndGetModule<RType::IAnimationModule>(RType::ModuleType::ANIMATION);
    _selectedView = std::make_shared<LoginView>(_window, *this, _graphicalModule, _provider);
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
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
            std::cout << "Return key pressed in OPTIONS state" << std::endl;
            setView(ViewState::MENU);
        }
    } else if (_viewState == ViewState::GAME) {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            std::cout << "Escape key pressed in GAME state" << std::endl;
            setView(ViewState::PAUSE);
        }
    } else if (_viewState == ViewState::PAUSE) {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            std::cout << "Escape key pressed in GAME state" << std::endl;
            setView(ViewState::GAME);
        }
    }
}

void RType::ClientViewport::launchWindow() {
    const float fixedTimeStep = 1.F / WINDOW_FPS;
    float accumulatedTime = 0.F;

    while (_window.isOpen()) {
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
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
}

void RType::ClientViewport::setView(ViewState state) {
    EntityPtr player;
    switch (state) {
        case ViewState::MENU:
            _selectedView = std::make_shared<MenuView>(_window, *this, _graphicalModule, _provider);
            break;
        case ViewState::OPTIONS:
            _selectedView = std::make_shared<OptionsView>(_window, *this, _graphicalModule, _provider);
            break;
        case ViewState::OPTIONSGAME:
            _selectedView = std::make_shared<OptionsView>(_window, *this, _graphicalModule, _provider, true);
            break;
        case ViewState::GAME:
            char buffer[50];
            _selectedView = std::make_shared<GameView>(_window, *this, _graphicalModule, _provider, _client->getUsername());
            sprintf(buffer, "player %d %s\n", _client->getClientID(), _client->getUsername().c_str());
            _client->sendMessage(MessageType::PLAYER_NAME, buffer);
            break;
        case ViewState::PAUSE:
            _selectedView = std::make_shared<PauseView>(_window, *this, _graphicalModule, _provider);
            break;
        case ViewState::LOGIN:
            _selectedView = std::make_shared<LoginView>(_window, *this, _graphicalModule, _provider);
            break;
        case ViewState::LOADSCREEN:
            _selectedView = std::make_shared<LoadView>(_window, *this, _graphicalModule, _client);
            break;
    }
    _selectedView->setPlayerEntity(_playerEntity);
    _viewState = state;
}

void RType::ClientViewport::addGraphicEntity(const GraphicEntityPtr &entity) {
    _graphicEntities.push_back(entity);
    std::cout << "Added entity with name: " << entity->getEntityName() << "\n";
}

RType::GraphicEntityPtr RType::ClientViewport::getGraphicEntityByName(const std::string &name) const {
    for (const auto &entity: _graphicEntities) {
        if (entity->getEntity()->getEntityName() == name)
            return entity;
    }
    return nullptr;
}

sf::Event RType::ClientViewport::getEvent() const {
    return event;
}

void RType::ClientViewport::connectToServer(const std::string &hostname, int port, std::string username) {
    std::cout << "Before try connecting to " << hostname << ":" << port << "\n";
    _client = std::make_shared<RType::UDPClient>(hostname, port, username, _window.getSize().x, _window.getSize().y);
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
    _window.clear();
    _selectedView->draw(_window, _graphicEntities);
    _window.display();
}

int RType::ClientViewport::start() {
    try {
        logInformation("Starting game view...");
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
        else std::cerr << "No handler found for message type: " << splitMessage[0] << "\n";
    };

    for (const auto &message : _client->pullQueue())
        handleMessage(message);
}

void RType::ClientViewport::setHandlers() {
    _handlers["player"] = [this](const std::vector<std::string> &splitMessage) { player(splitMessage); };
    _handlers["color"] = [this](const std::vector<std::string> &splitMessage) { changePlayerColor(splitMessage); };
    _handlers["bulletPlayer"] = [this](const std::vector<std::string> &splitMessage) { bulletPlayer(splitMessage); };
    _handlers["death"] = [this](const std::vector<std::string> &splitMessage) { death(splitMessage); };
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

RType::GraphicEntityPtr RType::ClientViewport::getGraphicEntity(const std::string &entityName) {
    for (auto &graphicEntity: _graphicEntities) {
        if (graphicEntity->getEntity()->getEntityName() == entityName)
            return graphicEntity;
    }
    return nullptr;
}

void RType::ClientViewport::destroyGraphicEntity(RType::GraphicEntityPtr entity) {
    auto it = std::find(_graphicEntities.begin(), _graphicEntities.end(), entity);

    if (it != _graphicEntities.end())
        _graphicEntities.erase(it);
}

void RType::ClientViewport::player(const std::vector<std::string> &splitMessage) {
    int sessionID = std::stoi(splitMessage[1]);
    std::string color =splitMessage[16];
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
    std::string color =splitMessage[16];
    std::string name = splitMessage[18];
    int score = std::stoi(splitMessage[20]);
    auto starshipEntity = _entityManager.createEntity();
    std::shared_ptr<RType::GraphicEntity> graphicStarship;


    starshipEntity->addComponent<RType::SpeedComponent>(speed);
    starshipEntity->addComponent<RType::HealthComponent>(health);
    starshipEntity->addComponent<RType::PositionComponent>(std::make_pair(positionX, positionY));
    starshipEntity->addComponent<RType::SizeComponent>(sizeX, sizeY);
    starshipEntity->addComponent<RType::SizeRectComponent>(rectX, rectY);
    starshipEntity->addComponent<RType::PlayerComponent>(true);
    starshipEntity->getComponent<RType::PlayerComponent>()->setUserName(name);
    starshipEntity->getComponent<RType::PlayerComponent>()->setScore(score);
    starshipEntity->setEntityName(color + " " + std::to_string(sessionID));
    if (starshipEntity->hasBaseComponents()) {
        graphicStarship = GraphicEntityFactory::createGraphicEntity(starshipEntity,"client/assets/sprites/r-typesheet42.gif", color);
        graphicStarship->loadSprite(_animationModule);
        if (sessionID == _client->getClientID()) {
            _playerEntity = graphicStarship;
            _selectedView->setPlayerEntity(graphicStarship);
            _client->setHealth(starshipEntity->getComponent<HealthComponent>()->getHealth());
            _client->setScore(starshipEntity->getComponent<PlayerComponent>()->getScore());
        }
        addGraphicEntity(graphicStarship);
    }
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
    std::string color =splitMessage[16];
    std::string name = splitMessage[18];
    int score = std::stoi(splitMessage[20]);
    EntityPtr starshipEntity = getGraphicEntity(color + " " + std::to_string(sessionID))->getEntity();

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
    bulletEntity = getGraphicEntity(entityName)->getEntity();

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
