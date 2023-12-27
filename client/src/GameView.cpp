/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.cpp
*/

#include ".././include/GameView.hpp"

RType::GameView::GameView() : _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Type"), _viewState(ViewState::MENU) {
    _window.setFramerateLimit(60);
}

void RType::GameView::handleInput(std::shared_ptr<AGraphicEntity> &entity) {
    sf::Sprite sprite = entity->getSprite();
    std::shared_ptr<Entity> gameEntity = entity->getEntity();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        entity->moveRight(sprite, gameEntity);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        entity->moveLeft(sprite, gameEntity);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        entity->moveUp(sprite, gameEntity);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        entity->moveDown(sprite, gameEntity);
    }
}

void RType::GameView::launchWindow(std::shared_ptr<AGraphicEntity> graphicEntities) {
    while (_window.isOpen()) {
        sf::Event event{};
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
                return;
            }
        }
        handleInput(graphicEntities);
        float deltaTime = animationClock.restart().asSeconds();
        updateEntities(deltaTime);
        draw();
    }
}

void RType::GameView::setView(ViewState state) {
    _viewState = state;
}

void RType::GameView::addGraphicEntity(std::shared_ptr<AGraphicEntity> entity) {
    graphicEntities.push_back(entity);
}

void RType::GameView::updateEntities(float deltaTime) {
    for (auto &entity: graphicEntities) {
        entity->update(deltaTime);
    }
}

void RType::GameView::draw() {
    _window.clear();
    for (auto &entity: graphicEntities) {
        entity->draw(_window);
    }
    _window.display();
}

int RType::GameView::start() {
    try {
        RType::EntityManager entityManager;

        auto starshipEntity = entityManager.createEntity();
        starshipEntity->addComponent<RType::SpeedComponent>(10);
        starshipEntity->addComponent<RType::PositionComponent>(std::make_pair(300, 30));

        std::shared_ptr<RType::GraphicEntity> graphicStarship;
        if (starshipEntity->hasComponents() == true) {
            graphicStarship = RType::GraphicEntityFactory::createGraphicEntity(starshipEntity);
            addGraphicEntity(graphicStarship);
            logInformation("Starting game view...");
            launchWindow(graphicStarship);
        }

    } catch (const std::exception &e) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
