/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once
#include "IDraw.hpp"

namespace RType {
    class DeadState : public IDraw {
    public:
        DeadState(sf::RenderWindow &window, GameView &gameView) : _gameView(gameView) {}
        void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>> graphicEntities) override {
        }
    private:
        GameView &_gameView;
    };
}