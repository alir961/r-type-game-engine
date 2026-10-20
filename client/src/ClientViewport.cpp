/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.cpp
*/

#include "../include/ClientViewport.hpp"
#include "engine/modules/animation/IAnimationModule.hpp"

RType::ClientViewport::ClientViewport() {
    _graphicalModule->openWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "R-Type");
    _menuBackground = std::make_unique<Background>(std::vector<std::string>{"client/assets/background/1.png",
                                                                            "client/assets/background/2.png",
                                                                            "client/assets/background/3.png",
                                                                            "client/assets/background/4.png"},
                                                   std::vector<float>{0.2F, 0.5F, 1.0F, 2.0F});
    _console = std::make_unique<ConsoleOverlay>();
    _selectedView = std::make_shared<LoginView>(*this);
    setHandlers();
    loadOptionalModules();
}

void RType::ClientViewport::loadOptionalModules() {
    for (const ModuleType type: {ModuleType::SOUND, ModuleType::PARTICLE, ModuleType::CONSOLE}) {
        try {
            _provider->loadModule(type);
        } catch (const std::exception &exception) {
            _logger->warn(std::string("Optional module not loaded: ") + exception.what());
        }
    }
    setupConsole();
}

void RType::ClientViewport::setupConsole() {
    IConsoleModule *console = ConsoleOverlay::getConsole();
    const auto onOff = [](bool value) { return std::string(value ? "on" : "off"); };

    if (console == nullptr)
        return;
    console->registerCommand("fps", "show or hide the frame rate", [this, onOff](const std::vector<std::string> &) {
        _showFps = !_showFps;
        return "FPS counter " + onOff(_showFps);
    });
    console->registerCommand("hitbox", "outline the collision boxes used by the server", [onOff](const std::vector<std::string> &) {
        GraphicEntity::showHitboxes = !GraphicEntity::showHitboxes;
        return "Hitboxes " + onOff(GraphicEntity::showHitboxes);
    });
    console->registerCommand("volume", "volume [0-100]: show or set the master volume", [](const std::vector<std::string> &args) {
        ISoundModule *sound = Audio::getModule();

        if (sound == nullptr)
            return std::string("The sound module is not loaded (Options)");
        if (!args.empty())
            sound->setVolume(std::stof(args[0]));
        return "Volume " + std::to_string(static_cast<int>(sound->getVolume()));
    });
    console->registerCommand("difficulty", "difficulty easy|normal|hard: change it for everyone on the server", [this](const std::vector<std::string> &args) {
        if (_client == nullptr)
            return std::string("Not connected to a server");
        if (args.empty())
            return "Difficulty: " + _difficulty;
        if (args[0] != "easy" && args[0] != "normal" && args[0] != "hard")
            return std::string("Usage: difficulty easy|normal|hard");
        requestDifficulty(args[0]);
        return "Difficulty set to " + args[0];
    });
    console->registerCommand("particles", "number of live particles", [](const std::vector<std::string> &) {
        IParticleModule *particles = Particles::getModule();

        return particles == nullptr ? std::string("The particle module is not loaded (Options)")
                                    : std::to_string(particles->getCount()) + " particles";
    });
    console->registerCommand("status", "connection and game state", [this](const std::vector<std::string> &) {
        if (_client == nullptr)
            return std::string("Not connected");
        return "Server " + _serverAddress + ", player #" + std::to_string(_client->getClientID()) + ", " +
               std::to_string(_graphicEntities.size()) + " entities on screen, difficulty " + _difficulty;
    });
    console->registerCommand("quit", "close the game", [this](const std::vector<std::string> &) {
        _graphicalModule->close();
        return std::string("Bye");
    });
}

void RType::ClientViewport::drawFps() {
    const float frameTime = _frameClock.restart().asSeconds();

    _fps = _fps == 0.0F ? 1.0F / std::max(frameTime, 0.001F) : _fps * 0.95F + 0.05F / std::max(frameTime, 0.001F);
    if (!_showFps)
        return;
    Label fps(std::to_string(static_cast<int>(_fps + 0.5F)) + " FPS", 24, Theme::Success, Theme::CENTER_X, 14.0F, Align::CENTER);
    fps.draw();
}

void RType::ClientViewport::handleGameInput() {
    using Key = sf::Keyboard;
    constexpr float SHOOT_COOLDOWN = 0.12F;
    char buffer[100];

    if (!_graphicalModule->hasFocus() || ConsoleOverlay::isOpen())
        return;
    if (Key::isKeyPressed(Key::Right) || Key::isKeyPressed(Key::D)) {
        sprintf(buffer, "move_right %d\n", _client->getClientID());
        _client->sendMessage(MessageType::MOVE_RIGHT, buffer);
    }

    if (Key::isKeyPressed(Key::Left) || Key::isKeyPressed(Key::A) || Key::isKeyPressed(Key::Q)) {
        sprintf(buffer, "move_left %d\n", _client->getClientID());
        _client->sendMessage(MessageType::MOVE_LEFT, buffer);
    }

    if (Key::isKeyPressed(Key::Up) || Key::isKeyPressed(Key::W) || Key::isKeyPressed(Key::Z)) {
        sprintf(buffer, "move_up %d\n", _client->getClientID());
        _client->sendMessage(MessageType::MOVE_UP, buffer);
    }

    if (Key::isKeyPressed(Key::Down) || Key::isKeyPressed(Key::S)) {
        sprintf(buffer, "move_down %d\n", _client->getClientID());
        _client->sendMessage(MessageType::MOVE_DOWN, buffer);
    }

    if (Key::isKeyPressed(Key::Space) && _shootClock.getElapsedTime().asSeconds() >= SHOOT_COOLDOWN) {
        sprintf(buffer, "bulletPlayer %d\n", _client->getClientID());
        _client->sendMessage(MessageType::SHOOT, buffer);
        _shootClock.restart();
    }
}

void RType::ClientViewport::handleGameEvent(const sf::Event &event) {
    char buffer[100];

    // One color change per key press, not one per frame while the key is held.
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {
        sprintf(buffer, "color %d\n", _client->getClientID());
        _client->sendMessage(MessageType::PLAYER_COLOR, buffer);
    }
}

bool RType::ClientViewport::isInGame() const {
    switch (_viewState) {
        case ViewState::GAME:
        case ViewState::PAUSE:
        case ViewState::OPTIONSGAME:
        case ViewState::HOWTOPLAYGAME:
            return _client != nullptr;
        default:
            return false;
    }
}

void RType::ClientViewport::launchWindow() {
    const float fixedTimeStep = 1.F / WINDOW_FPS;

    while (_graphicalModule->isOpen()) {
        while (_graphicalModule->pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                _graphicalModule->close();
                closeConnectionToServer();
                return;
            }
            // An open console takes the keyboard.
            if (_console->handleEvent(_event))
                continue;
            if (_viewState == ViewState::GAME)
                handleGameEvent(_event);
            _selectedView->handleEvent(_event);
            applyPendingView();
        }
        // The server keeps simulating while the pause menu is open, so stay in sync.
        if (isInGame()) {
            char buffer[100];
            handleMessageFromServer();
            if (_viewState == ViewState::GAME)
                handleGameInput();
            sprintf(buffer, "tick %d\n", _client->getClientID());
            _client->sendMessage(MessageType::TICK, buffer);
        }
        updateEntities(fixedTimeStep);
        _selectedView->update();
        draw();
        applyPendingView();
    }
    _logger->info("Exit game");
}

void RType::ClientViewport::setView(ViewState state) {
    // Views call this from their own methods: switching right away would destroy
    // the view while it is still running, so the switch happens at the next safe point.
    _pendingView = state;
}

void RType::ClientViewport::applyPendingView() {
    if (!_pendingView.has_value())
        return;
    const ViewState state = *_pendingView;

    _pendingView.reset();
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
            _selectedView = std::make_shared<GameView>(*this, _explosions);
            // Coming back from the pause menu must not respawn the player.
            if (!isInGame()) {
                char buffer[50];

                sprintf(buffer, "player %d %s\n", _client->getClientID(), _client->getUsername().c_str());
                _client->sendMessage(MessageType::PLAYER_NAME, buffer);
            }
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
        case ViewState::DEAD:
            _selectedView = std::make_shared<WinDeadView>(*this);
            break;
        case ViewState::HOWTOPLAY:
            _selectedView = std::make_shared<HowToPlayView>(*this);
            break;
        case ViewState::HOWTOPLAYGAME:
            _selectedView = std::make_shared<HowToPlayView>(*this, true);
            break;
        case ViewState::DIFFICULTY:
            _selectedView = std::make_shared<DifficultyView>(*this);
            break;
    }
    _selectedView->setPlayerEntity(_playerEntity);
    _viewState = state;
    // Music while a game runs (pause menus included), a jingle on game over, silence in the menus.
    if (isInGame())
        Audio::playMusic("music");
    else
        Audio::stopMusic();
    if (state == ViewState::DEAD)
        Audio::play("game_over", 80.0F);
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
    _serverAddress = hostname + ":" + std::to_string(port);
    _logger->warn("Connection attempt to server " + _serverAddress);
    _client = std::make_shared<RType::UDPClient>(hostname, port, username, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void RType::ClientViewport::requestDifficulty(const std::string &difficulty) {
    char buffer[100];

    if (_client == nullptr)
        return;
    sprintf(buffer, "difficulty %d %s\n", _client->getClientID(), difficulty.c_str());
    _client->sendMessage(MessageType::DIFFICULTY, buffer);
    _difficulty = difficulty;
}

void RType::ClientViewport::closeConnectionToServer() {
    _client = nullptr;
    _playerEntity = nullptr;
    _graphicEntities.clear();
    _explosions.clear();
}

void RType::ClientViewport::updateEntities(float deltaTime) {
    for (const auto &entity: _graphicEntities)
        entity->update(deltaTime);
    for (const auto &explosion: _explosions)
        explosion->update(deltaTime);
    std::erase_if(_explosions, [](const ExplosionPtr &explosion) { return explosion->isFinished(); });
    if (IParticleModule *particles = Particles::getModule())
        particles->update(deltaTime);
}

void RType::ClientViewport::draw() {
    _graphicalModule->clear();
    // The game view draws its own background; every menu shares the starfield.
    if (_viewState != ViewState::GAME) {
        _menuBackground->update(1.F / WINDOW_FPS);
        _menuBackground->draw();
    }
    _selectedView->draw(_graphicEntities);
    drawFps();
    _console->draw();
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
    _handlers["monster"] = [this](const std::vector<std::string> &splitMessage) { monster(splitMessage); };
    _handlers["static"] = [this](const std::vector<std::string> &splitMessage) { staticEntity(splitMessage); };
    _handlers["starship"] = [this](const std::vector<std::string> &splitMessage) { starship(splitMessage); };
    _handlers["bulletStarship"] = [this](const std::vector<std::string> &splitMessage) { bulletStarship(splitMessage); };
    _handlers["difficulty"] = [this](const std::vector<std::string> &splitMessage) {
        if (splitMessage.size() >= 2)
            _difficulty = splitMessage[1];
    };
}

void RType::ClientViewport::changePlayerColor(const std::vector<std::string> &splitMessage) {
    const std::string sessionID = splitMessage[1];
    const std::string &color = splitMessage[2];

    // Rename the ship of whoever changed color (not always ours); its sprite follows the name.
    for (const auto &graphicEntity: _graphicEntities) {
        const EntityPtr &entity = graphicEntity->getEntity();
        const std::vector<std::string> name = Split::split(entity->getEntityName(), " \n");

        if (name.size() == 2 && name[0].ends_with("Player") && name[1] == sessionID) {
            entity->setEntityName(color + "Player " + sessionID);
            return;
        }
    }
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
    // Ships and monsters blow up; shots leave a few sparks where they hit.
    const auto center = std::dynamic_pointer_cast<GraphicEntity>(graphicEntity)->getCenter();
    if (!entityName.starts_with("bullet")) {
        const auto &[sizeX, sizeY] = entity->getComponent<SizeComponent>()->getSize();
        const float width = sizeX * entity->getComponent<SizeRectComponent>()->getSize().first;

        _explosions.push_back(std::make_shared<Explosion>(center, std::max(1.5F, width / 30.0F)));
        Particles::explosion(center, std::max(1.0F, width / 70.0F));
        Audio::play("explosion", graphicEntity == _playerEntity ? 100.0F : 55.0F);
    } else if (center.first > 20.0F && center.first < static_cast<float>(WINDOW_WIDTH) - 60.0F) {
        Particles::sparks(center, entityName.starts_with("bulletPlayer") ? Color::RGB{120, 220, 255, 255} : Color::RGB{255, 140, 60, 255}, 6);
    }
    if (_playerEntity != nullptr && graphicEntity == _playerEntity) {
        _client->setHealth(_playerEntity->getEntity()->getComponent<HealthComponent>()->getHealth());
        _client->setScore(_playerEntity->getEntity()->getComponent<PlayerComponent>()->getScore());
        _playerEntity = nullptr;
        setView(ViewState::DEAD);
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


void RType::ClientViewport::monster(const std::vector<std::string> &splitMessage) {
    int monsterID = std::stoi(splitMessage[1]);
    GraphicEntityPtr entity = getGraphicEntityByName("monster " + std::to_string(monsterID));

    if (entity == nullptr)
        createNewMonster(splitMessage);
    else
        updateMonster(splitMessage);
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
    GraphicEntityPtr graphicStarship;


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
        graphicStarship = GraphicEntityFactory::createStarship(starshipEntity, color);
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
    std::string color = splitMessage[16];
    std::string name = splitMessage[18];
    int score = std::stoi(splitMessage[20]);
    EntityPtr starshipEntity = getGraphicEntityByName(color + " " + std::to_string(sessionID))->getEntity();
    const int previousHealth = starshipEntity->getComponent<RType::HealthComponent>()->getHealth();

    starshipEntity->getComponent<RType::SpeedComponent>()->setSpeed(speed);
    starshipEntity->getComponent<RType::HealthComponent>()->setHealth(health);
    starshipEntity->getComponent<RType::PositionComponent>()->setPositions(std::make_pair(positionX, positionY));
    starshipEntity->getComponent<RType::SizeComponent>()->setSize(sizeX, sizeY);
    starshipEntity->getComponent<RType::SizeRectComponent>()->setSize(rectX, rectY);
    starshipEntity->getComponent<RType::PlayerComponent>()->setUserName(name);
    starshipEntity->getComponent<RType::PlayerComponent>()->setScore(score);
    if (sessionID == _client->getClientID()) {
        _client->setScore(score);
        _client->setHealth(health);
        if (health < previousHealth)
            Audio::play("hit", 80.0F);
    }
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
    GraphicEntityPtr graphicBullet;
    auto bulletEntity = _entityManager.createEntity();
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
    graphicBullet = GraphicEntityFactory::createBullet(bulletEntity, "bulletPlayer");
    addGraphicEntity(graphicBullet);
    Audio::play("shoot", sessionID == _client->getClientID() ? 30.0F : 10.0F);
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

void RType::ClientViewport::createNewMonster(const std::vector<std::string> &splitMessage) {
    int monsterID = std::stoi(splitMessage[1]);
    int speed = std::stoi(splitMessage[3]);
    int health = std::stoi(splitMessage[5]);
    float positionX = std::stof(splitMessage[7]);
    float positionY = std::stof(splitMessage[8]);
    float sizeX = std::stof(splitMessage[10]);
    float sizeY = std::stof(splitMessage[11]);
    float rectX = std::stof(splitMessage[13]);
    float rectY = std::stof(splitMessage[14]);
    auto monsterEntity = _entityManager.createEntity();
    char entityName[250];
    GraphicEntityPtr graphicMonster;

    sprintf(entityName, "monster %d", monsterID);
    monsterEntity->addComponent<RType::SpeedComponent>(speed);
    monsterEntity->addComponent<RType::HealthComponent>(health);
    monsterEntity->addComponent<RType::PositionComponent>(std::make_pair(positionX, positionY));
    monsterEntity->addComponent<RType::SizeComponent>(sizeX, sizeY);
    monsterEntity->addComponent<RType::SizeRectComponent>(rectX, rectY);
    monsterEntity->addComponent<RType::PlayerComponent>(false);
    monsterEntity->setEntityName(entityName);
    graphicMonster = GraphicEntityFactory::createMonster(monsterEntity, "monster");
    addGraphicEntity(graphicMonster);
}

void RType::ClientViewport::updateMonster(const std::vector<std::string> &splitMessage) {
    int monsterID = std::stoi(splitMessage[1]);
    int speed = std::stoi(splitMessage[3]);
    int health = std::stoi(splitMessage[5]);
    float positionX = std::stof(splitMessage[7]);
    float positionY = std::stof(splitMessage[8]);
    float sizeX = std::stof(splitMessage[10]);
    float sizeY = std::stof(splitMessage[11]);
    float rectX = std::stof(splitMessage[13]);
    float rectY = std::stof(splitMessage[14]);
    char entityName[250];
    EntityPtr monsterEntity;

    sprintf(entityName, "monster %d", monsterID);
    monsterEntity = getGraphicEntityByName(entityName)->getEntity();

    monsterEntity->getComponent<RType::SpeedComponent>()->setSpeed(speed);
    monsterEntity->getComponent<RType::HealthComponent>()->setHealth(health);
    monsterEntity->getComponent<RType::PositionComponent>()->setPositions(std::make_pair(positionX, positionY));
    monsterEntity->getComponent<RType::SizeComponent>()->setSize(sizeX, sizeY);
    monsterEntity->getComponent<RType::SizeRectComponent>()->setSize(rectX, rectY);
}

void RType::ClientViewport::staticEntity(const std::vector<std::string> &splitMessage) {
    int monsterID = std::stoi(splitMessage[1]);
    GraphicEntityPtr entity = getGraphicEntityByName("static " + std::to_string(monsterID));

    if (entity == nullptr)
        createNewStatic(splitMessage);
    else
        updateStatic(splitMessage);
}

void RType::ClientViewport::createNewStatic(const std::vector<std::string> &splitMessage) {
    int monsterID = std::stoi(splitMessage[1]);
    float positionX = std::stof(splitMessage[3]);
    float positionY = std::stof(splitMessage[4]);
    float sizeX = std::stof(splitMessage[6]);
    float sizeY = std::stof(splitMessage[7]);
    float rectX = std::stof(splitMessage[9]);
    float rectY = std::stof(splitMessage[10]);
    auto staticEntity = _entityManager.createEntity();
    char entityName[250];
    GraphicEntityPtr graphicStatic;

    sprintf(entityName, "static %d", monsterID);
    staticEntity->addComponent<RType::PositionComponent>(std::make_pair(positionX, positionY));
    staticEntity->addComponent<RType::SizeComponent>(sizeX, sizeY);
    staticEntity->addComponent<RType::SizeRectComponent>(rectX, rectY);
    staticEntity->addComponent<RType::PlayerComponent>(false);
    staticEntity->setEntityName(entityName);
    graphicStatic = GraphicEntityFactory::createStatic(staticEntity, "static");
    addGraphicEntity(graphicStatic);
}

void RType::ClientViewport::updateStatic(const std::vector<std::string> &splitMessage) {

}

void RType::ClientViewport::createNewStarship(const std::vector<std::string> &splitMessage) {
    int monsterID = std::stoi(splitMessage[1]);
    int speed = std::stoi(splitMessage[3]);
    int health = std::stoi(splitMessage[5]);
    float positionX = std::stof(splitMessage[7]);
    float positionY = std::stof(splitMessage[8]);
    float sizeX = std::stof(splitMessage[10]);
    float sizeY = std::stof(splitMessage[11]);
    float rectX = std::stof(splitMessage[13]);
    float rectY = std::stof(splitMessage[14]);
    auto monsterEntity = _entityManager.createEntity();
    char entityName[250];
    GraphicEntityPtr graphicMonster;

    sprintf(entityName, "starship %d", monsterID);
    monsterEntity->addComponent<RType::SpeedComponent>(speed);
    monsterEntity->addComponent<RType::HealthComponent>(health);
    monsterEntity->addComponent<RType::PositionComponent>(std::make_pair(positionX, positionY));
    monsterEntity->addComponent<RType::SizeComponent>(sizeX, sizeY);
    monsterEntity->addComponent<RType::SizeRectComponent>(rectX, rectY);
    monsterEntity->addComponent<RType::PlayerComponent>(false);
    monsterEntity->setEntityName(entityName);
    graphicMonster = GraphicEntityFactory::createEnemyStarship(monsterEntity, "starship");
    addGraphicEntity(graphicMonster);
}

void RType::ClientViewport::updateStarship(const std::vector<std::string> &splitMessage) {
    int monsterID = std::stoi(splitMessage[1]);
    int speed = std::stoi(splitMessage[3]);
    int health = std::stoi(splitMessage[5]);
    float positionX = std::stof(splitMessage[7]);
    float positionY = std::stof(splitMessage[8]);
    float sizeX = std::stof(splitMessage[10]);
    float sizeY = std::stof(splitMessage[11]);
    float rectX = std::stof(splitMessage[13]);
    float rectY = std::stof(splitMessage[14]);
    char entityName[250];
    EntityPtr monsterEntity;

    sprintf(entityName, "starship %d", monsterID);
    monsterEntity = getGraphicEntityByName(entityName)->getEntity();

    monsterEntity->getComponent<RType::SpeedComponent>()->setSpeed(speed);
    monsterEntity->getComponent<RType::HealthComponent>()->setHealth(health);
    monsterEntity->getComponent<RType::PositionComponent>()->setPositions(std::make_pair(positionX, positionY));
    monsterEntity->getComponent<RType::SizeComponent>()->setSize(sizeX, sizeY);
    monsterEntity->getComponent<RType::SizeRectComponent>()->setSize(rectX, rectY);
}

void RType::ClientViewport::createNewStarshipBullet(const std::vector<std::string> &splitMessage) {
    GraphicEntityPtr graphicBullet;
    auto bulletEntity = _entityManager.createEntity();
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
    sprintf(entityName, "bulletStarship %d %d", sessionID, bulletID);
    bulletEntity->setEntityName(entityName);
    graphicBullet = GraphicEntityFactory::createBulletStarship(bulletEntity, "bulletStarship");
    addGraphicEntity(graphicBullet);
    Audio::play("enemy_shoot", 25.0F);
}

void RType::ClientViewport::updateStarshipBullet(const std::vector<std::string> &splitMessage) {
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

    sprintf(entityName, "bulletStarship %d %d", sessionID, bulletID);
    bulletEntity = getGraphicEntityByName(entityName)->getEntity();

    bulletEntity->getComponent<RType::SpeedComponent>()->setSpeed(speed);
    bulletEntity->getComponent<RType::DamageComponent>()->setDamage(damage);
    bulletEntity->getComponent<RType::PositionComponent>()->setPositions(std::make_pair(positionX, positionY));
    bulletEntity->getComponent<RType::SizeComponent>()->setSize(sizeX, sizeY);
    bulletEntity->getComponent<RType::SizeRectComponent>()->setSize(rectX, rectY);
}

void RType::ClientViewport::starship(const std::vector<std::string> &splitMessage) {
    int monsterID = std::stoi(splitMessage[1]);
    GraphicEntityPtr entity = getGraphicEntityByName("starship " + std::to_string(monsterID));

    if (entity == nullptr)
        createNewStarship(splitMessage);
    else
        updateStarship(splitMessage);
}

void RType::ClientViewport::bulletStarship(const std::vector<std::string> &splitMessage) {
    int sessionID = std::stoi(splitMessage[1]);
    int bulletID = std::stoi(splitMessage[2]);
    std::string entityName = splitMessage[0];
    GraphicEntityPtr entity = getGraphicEntityByName(entityName + " " + std::to_string(sessionID) + " " + std::to_string(bulletID));

    if (entity == nullptr)
        createNewStarshipBullet(splitMessage);
    else
        updateStarshipBullet(splitMessage);
}
