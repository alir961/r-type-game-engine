/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.cpp
*/

#include "../include/GameView.hpp"

RType::GameView::GameView(IGraphicalModule *graphicalModule, asio::io_context &ioContext, UDP::endpoint endpoint) :
        _client(ioContext, std::move(endpoint)),
        _graphicalModule(graphicalModule) {
    _window.setFramerateLimit(WINDOW_FPS);
    _menuState = std::make_shared<MenuState>(_window, *this, _graphicalModule);
    _optionsState = std::make_shared<OptionsState>(_window, *this, _graphicalModule);
    _pauseState = std::make_shared<PauseState>(_window, *this, _graphicalModule);
    _deadState = std::make_shared<DeadState>(_window, *this, _graphicalModule);
    _winState = std::make_shared<WinState>(_window, *this, _graphicalModule);
    _gameState = std::make_shared<GameState>(_window, *this, _graphicalModule);
    _loginState = std::make_shared<LoginState>(_window, *this, _graphicalModule);
}

void RType::GameView::handleInput(const GraphicEntityPtr &entity) const {
    sf::Sprite sprite = entity->getSprite();
    std::shared_ptr<Entity> gameEntity = entity->getEntity();

    if (_viewState != ViewState::GAME)
        return;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) entity->moveRight(sprite, gameEntity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) entity->moveLeft(sprite, gameEntity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) entity->moveUp(sprite, gameEntity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) entity->moveDown(sprite, gameEntity);
}

void RType::GameView::basicInput() {
    // Testing Win/Lose State
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad8) {
        std::cout << "Entering Win State" << '\n';
        setView(ViewState::WIN);
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad9) {
        std::cout << "Entering Lose State" << '\n';
        setView(ViewState::DEAD);
    }
    // Testing Win/Lose State
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

void RType::GameView::launchWindow(const GraphicEntityPtr &entity) {
    const float fixedTimeStep = 1.F / WINDOW_FPS;
    float accumulatedTime = 0.F;

    while (_window.isOpen()) {
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
                return;
            }
            basicInput();
            _client.startReceive();
        }
        handleInput(entity);

        accumulatedTime += animationClock.restart().asSeconds();
        while (accumulatedTime >= fixedTimeStep) {
            updateEntities(fixedTimeStep);
            accumulatedTime -= fixedTimeStep;
        }
        draw();
    }
}

void RType::GameView::setView(ViewState state) {
    _viewState = state;
}

void RType::GameView::addGraphicEntity(std::shared_ptr<AGraphicEntity> entity) {
    _graphicEntities.push_back(entity);
    std::cout << "Added entity with name: " << entity->getEntityName() << std::endl;
}

void RType::GameView::updateEntities(float deltaTime) {
    for (const auto &entity: _graphicEntities) {
        entity->update(deltaTime);
        _menuState->update();
        _optionsState->update();
        _pauseState->update();
    }
    switch (_viewState) {
        case ViewState::MENU:
            _menuState->update();
            break;
        case ViewState::OPTIONS:
            _optionsState->update();
            break;
        case ViewState::PAUSE:
            _pauseState->update();
            break;
        case ViewState::LOGIN:
            _loginState->update();
            break;
        case ViewState::DEAD:
            _deadState->update();
            break;
        case ViewState::WIN:
            _winState->update();
            break;
        default:
            break;
    }
}

void RType::GameView::draw() {
    _window.clear();
    switch (_viewState) {
        using enum RType::ViewState;
        case MENU:
            _menuState->draw(_window, _graphicEntities);
            break;
        case OPTIONS:
            _optionsState->draw(_window, _graphicEntities);
            break;
        case GAME:
            _gameState->draw(_window, _graphicEntities);
            break;
        case PAUSE:
            _pauseState->draw(_window, _graphicEntities);
            break;
        case DEAD:
            _deadState->draw(_window, _graphicEntities);
            break;
        case WIN:
            _winState->draw(_window, _graphicEntities);
            break;
        case LOGIN:
            _loginState->draw(_window, _graphicEntities);
            break;
        default:
            break;
    }
    _window.display();
}

int RType::GameView::start() {
    try {
        RType::EntityManager entityManager;

        auto starshipEntity = entityManager.createEntity();
        starshipEntity->addComponent<RType::SpeedComponent>(10);
        starshipEntity->addComponent<RType::HealthComponent>(100);
        starshipEntity->addComponent<RType::PositionComponent>(std::make_pair(300, 30));
        starshipEntity->addComponent<RType::PlayerComponent>(true);

        std::shared_ptr<RType::GraphicEntity> graphicStarship;
        if (starshipEntity->hasComponents()) {
            graphicStarship = RType::GraphicEntityFactory::createGraphicEntity(starshipEntity, "client/assets/r-typesheet42.gif", "playerStarship");
            addGraphicEntity(graphicStarship);
            logInformation("Starting game view...");
            launchWindow(graphicStarship);
        }
    } catch (const std::exception &e) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
