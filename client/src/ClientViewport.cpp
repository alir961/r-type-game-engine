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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _client->sendMessage(MessageType::MOVE_RIGHT, std::format("move_right {}\n", _client->getClientID()));
    };
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _client->sendMessage(MessageType::MOVE_LEFT, std::format("move_left {}\n", _client->getClientID()));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _client->sendMessage(MessageType::MOVE_UP, std::format("move_up {}\n", _client->getClientID()));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _client->sendMessage(MessageType::MOVE_DOWN, std::format("move_down {}\n", _client->getClientID()));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        _client->sendMessage(MessageType::SHOOT, std::format("shoot {}\n", _client->getClientID()));
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
    } else if (_viewState == ViewState::WIN || _viewState == ViewState::DEAD) {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            setView(ViewState::MENU);
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
            handleMessageFromServer();
            handleInput();
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
            _selectedView = std::make_shared<GameView>(_window, *this, _graphicalModule, _provider, _client->getUsername());
            break;
        case ViewState::PAUSE:
            _selectedView = std::make_shared<PauseView>(_window, *this, _graphicalModule, _provider);
            break;
        case ViewState::DEAD:
            _selectedView = std::make_shared<DeadView>(_window, *this, _graphicalModule, _provider);
            break;
        case ViewState::LOGIN:
            _selectedView = std::make_shared<LoginView>(_window, *this, _graphicalModule, _provider);
            break;
        case ViewState::LOADSCREEN:
            _selectedView = std::make_shared<LoadView>(_window, *this, _graphicalModule, _client);
            break;
        case ViewState::WIN:
            _selectedView = std::make_shared<WinView>(_window, *this, _graphicalModule, _provider);
            break;
    }
    _viewState = state;
}

void RType::ClientViewport::addGraphicEntity(const GraphicEntityPtr &entity) {
    _graphicEntities.push_back(entity);
    std::cout << "Added entity with name: " << entity->getEntityName() << "\n";
}

RType::GraphicEntityPtr RType::ClientViewport::getGraphicEntityByName(const std::string &name) const {
    for (const auto &entity: _graphicEntities) {
        if (entity->getEntityName() == name)
            return entity;
    }
    std::cerr << "Unable to find entity " << name << "\n";
    return nullptr;
}

sf::Event RType::ClientViewport::getEvent() const {
    return event;
}

void RType::ClientViewport::connectToServer(const std::string &hostname, int port, std::string username) {
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

void RType::ClientViewport::newPlayer(const std::vector<std::string> &splitMessage) {
    int sessionID = std::stoi(splitMessage[1]);
    int speed = std::stoi(splitMessage[3]);
    int health = std::stoi(splitMessage[5]);
    int positionX = std::stoi(splitMessage[7]);
    int positionY = std::stoi(splitMessage[8]);
    float sizeX = std::stof(splitMessage[10]);
    float sizeY = std::stof(splitMessage[11]);
    float rectX = std::stof(splitMessage[13]);
    float rectY = std::stof(splitMessage[14]);
    auto starshipEntity = _entityManager.createEntity();
    std::shared_ptr<RType::GraphicEntity> graphicStarship;

    starshipEntity->addComponent<RType::SpeedComponent>(speed);
    starshipEntity->addComponent<RType::HealthComponent>(health);
    starshipEntity->addComponent<RType::PositionComponent>(std::make_pair(positionX, positionY));
    starshipEntity->addComponent<RType::SizeComponent>(sizeX, sizeY);
    starshipEntity->addComponent<RType::SizeRectComponent>(rectX, rectY);
    starshipEntity->addComponent<RType::PlayerComponent>(true);
    starshipEntity->getComponent<RType::PlayerComponent>()->setUserName(_client->getUsername());
    if (starshipEntity->hasBaseComponents()) {
        graphicStarship = GraphicEntityFactory::createGraphicEntity(starshipEntity,"client/assets/sprites/r-typesheet42.gif","playerStarship");
        graphicStarship->loadSprite(_animationModule);
        if (sessionID == _client->getClientID())
            _playerEntity = graphicStarship;
        addGraphicEntity(graphicStarship);
    }
}

void RType::ClientViewport::setHandlers() {
    _handlers["player"] = [this](const std::vector<std::string> &splitMessage) { newPlayer(splitMessage); };
    _handlers["move_left"] = [this](const std::vector<std::string> &splitMessage) { moveLeft(splitMessage); };
    _handlers["move_right"] = [this](const std::vector<std::string> &splitMessage) { moveRight(splitMessage); };
    _handlers["move_up"] = [this](const std::vector<std::string> &splitMessage) { moveUp(splitMessage); };
    _handlers["move_down"] = [this](const std::vector<std::string> &splitMessage) { moveDown(splitMessage); };
    _handlers["shoot"] = [this](const std::vector<std::string> &splitMessage) { shoot(splitMessage); };
}

void RType::ClientViewport::moveLeft(const std::vector<std::string> &splitMessage) {
    sf::Sprite sprite = _playerEntity->getSprite();
    EntityPtr gameEntity = _playerEntity->getEntity();
    std::string status = splitMessage[2];

    if (status == "ok")
        _playerEntity->moveLeft(sprite, gameEntity);
    else
        setView(ViewState::DEAD);
}

void RType::ClientViewport::moveRight(const std::vector<std::string> &splitMessage) {
    sf::Sprite sprite = _playerEntity->getSprite();
    EntityPtr gameEntity = _playerEntity->getEntity();
    const std::string &status = splitMessage[2];

    if (status == "ok")
        _playerEntity->moveRight(sprite, gameEntity);
    else
        setView(ViewState::DEAD);
}

void RType::ClientViewport::moveDown(const std::vector<std::string> &splitMessage) {
    sf::Sprite sprite = _playerEntity->getSprite();
    EntityPtr gameEntity = _playerEntity->getEntity();
    const std::string &status = splitMessage[2];

    if (status == "ok")
        _playerEntity->moveDown(sprite, gameEntity);
    else
        setView(ViewState::DEAD);
}

void RType::ClientViewport::moveUp(const std::vector<std::string> &splitMessage) {
    sf::Sprite sprite = _playerEntity->getSprite();
    EntityPtr gameEntity = _playerEntity->getEntity();
    const std::string &status = splitMessage[2];

    if (status == "ok")
        _playerEntity->moveUp(sprite, gameEntity);
    else
        setView(ViewState::DEAD);
}

void RType::ClientViewport::shoot(const std::vector<std::string> &splitMessage) {
    auto bulletEntity = _entityManager.createEntity();
    std::shared_ptr<RType::GraphicEntity> graphicBullet;
    int speed = std::stoi(splitMessage[3]);
    int damage = std::stoi(splitMessage[5]);
    std::string status = splitMessage[6];

    bulletEntity->addComponent<RType::SpeedComponent>(speed);
    bulletEntity->addComponent<RType::DamageComponent>(damage);
    bulletEntity->addComponent<RType::PositionComponent>(std::make_pair(_playerEntity->getEntity()->getComponent<PositionComponent>()->getPositions().first, _playerEntity->getEntity()->getComponent<PositionComponent>()->getPositions().second));
    bulletEntity->addComponent<RType::SizeComponent>(1.0f, 1.0f);
    graphicBullet = GraphicEntityFactory::createGraphicEntity(bulletEntity, "client/assets/sprites/r-typesheet5.gif", "playerStarship");
    addGraphicEntity(graphicBullet);
    sf::Sprite sprite = graphicBullet->getSprite();
    EntityPtr gameEntity = graphicBullet->getEntity();
    if (status == "ok")
        graphicBullet->moveRight(sprite, gameEntity);
}
