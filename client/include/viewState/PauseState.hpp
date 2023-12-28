/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once
#include "IDraw.hpp"
#include "../graphicalComponents/TextBox.hpp"

namespace RType {
    class GameView;
    enum class ViewState;

    class PauseState : public IDraw {
    public:
        PauseState(sf::RenderWindow &window, GameView &gameView)
            : mainMenu(window, sf::Color::Cyan, 100.0f, 200.0f, "Exit To Main Menu"), _gameView(gameView) {}

        void handleInput() {
            mainMenu.handleInput();

            if (isMouseClicked()) {
                if (mainMenu.getActive()) {
                    std::cout << "Exit To Main Menu!" << std::endl;
                    _gameView.setView(ViewState::MENU);
                }
            }
        }

        void update() {
            mainMenu.update();
        }

        void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>>) override {
            mainMenu.draw();
            handleInput();
        }

    private:
        TextBox mainMenu;
        GameView &_gameView;

        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
