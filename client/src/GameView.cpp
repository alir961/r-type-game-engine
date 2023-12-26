/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.cpp
*/

#include "GameView.hpp"

GameView::GameView() : _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Type"), _viewState(ViewState::MENU) {
    _window.setFramerateLimit(60);
}

void GameView::start() {
    while (_window.isOpen()) {
        sf::Event event{};
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
                return;
            }
        }
        float deltaTime = animationClock.restart().asSeconds();
        updateEntities(deltaTime);
        draw();
    }
}

void GameView::setView(ViewState state) {
    _viewState = state;
}

void GameView::addGraphicEntity(std::shared_ptr<IGraphicEntity> entity) {
    graphicEntities.push_back(entity);
}

void GameView::updateEntities(float deltaTime) {
    for (auto &entity: graphicEntities) {
        entity->update(deltaTime);
    }
}

void GameView::draw() {
    _window.clear();
    for (auto &entity: graphicEntities) {
        entity->draw(_window);
    }
    _window.display();
}
