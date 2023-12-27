/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once
#include "IDraw.hpp"

namespace RType {
    class GameView;
    enum class ViewState;

    class OptionsState : public IDraw {
    public:
        OptionsState(sf::RenderWindow &window, GameView &gameView)
            : _gameView(gameView) {}

        void handleInput() {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                std::cout << "Return key pressed" << std::endl;
                _gameView.setView(ViewState::MENU);
            }
        }

        void update() {
        }

        void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>>) override {
            handleInput();
        }

    private:
        GameView &_gameView;

        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
