/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "../include/GameView.hpp"

void RType::GameView::draw() {
    _window.clear();
}

void RType::GameView::start() {
    draw();

    while (_window.isOpen()) {
        sf::Event event{};

        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
                return;
            }
        }
        draw();
    }
}

void RType::GameView::setView(RType::ViewState state) {
    _viewState = state;
}
