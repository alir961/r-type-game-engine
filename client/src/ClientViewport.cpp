/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.cpp
*/

#include "../include/ClientViewport.hpp"

RType::ClientViewport::ClientViewport() {
    _window.setFramerateLimit(WINDOW_FPS);
    _graphicalModule = _provider.loadAndGetModule<RType::IGraphicalModule>(RType::ModuleType::GRAPHICAL);
    _selectedView = std::make_shared<LoginView>(_window, *this, _graphicalModule, _provider);
}

void RType::ClientViewport::handleInput(const GraphicEntityPtr &entity) const {
    sf::Sprite sprite = entity->getSprite();
    EntityPtr gameEntity = entity->getEntity();

    if (_viewState != ViewState::GAME)
        return;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) entity->moveRight(sprite, gameEntity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) entity->moveLeft(sprite, gameEntity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) entity->moveUp(sprite, gameEntity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) entity->moveDown(sprite, gameEntity);
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

void RType::ClientViewport::launchWindow(const GraphicEntityPtr &entity) {
    const float fixedTimeStep = 1.F / WINDOW_FPS;
    float accumulatedTime = 0.F;

    while (_window.isOpen()) {
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
                return;
            }
            basicInput();
        }
        handleInput(entity);

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
            _selectedView = std::make_shared<GameView>(_window, *this, _graphicalModule, _provider);
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
        case ViewState::WIN:
            _selectedView = std::make_shared<WinView>(_window, *this, _graphicalModule, _provider);
            break;
    }
    _viewState = state;
}

void RType::ClientViewport::addGraphicEntity(std::shared_ptr<AGraphicEntity> entity) {
    _graphicEntities.push_back(entity);
    std::cout << "Added entity with name: " << entity->getEntityName() << std::endl;
}

void RType::ClientViewport::updateEntities(float deltaTime) {
    for (const auto &entity: _graphicEntities) {
        entity->update(deltaTime);
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
        RType::EntityManager entityManager;

        auto starshipEntity = entityManager.createEntity();
        starshipEntity->addComponent<RType::SpeedComponent>(10);
        starshipEntity->addComponent<RType::HealthComponent>(100);
        starshipEntity->addComponent<RType::PositionComponent>(std::make_pair(300, 30));
        starshipEntity->addComponent<RType::SizeComponent>(2.0f, 2.0f);
        starshipEntity->addComponent<RType::PlayerComponent>(true);

        std::shared_ptr<RType::GraphicEntity> graphicStarship;
        if (starshipEntity->hasBaseComponents()) {
            graphicStarship = RType::GraphicEntityFactory::createGraphicEntity(starshipEntity,"client/assets/sprites/r-typesheet42.gif","playerStarship");
            addGraphicEntity(graphicStarship);
            logInformation("Starting game view...");
            launchWindow(graphicStarship);
        }
    } catch (const std::exception &e) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
