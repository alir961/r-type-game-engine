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

    class OptionsState : public IDraw {
    public:
        OptionsState(sf::RenderWindow &window, GameView &gameView)
            : title(window, sf::Color::Cyan, 30, window.getSize().x / 2.0f, 50.0f, "Options"),
              mainMenu(window, sf::Color::Cyan, 20, 500.0f, 195.0f, "Exit To Main Menu"), _gameView(gameView) {}

        void handleInput() {
            title.handleInput();
            mainMenu.handleInput();

            if (isMouseClicked()) {
                if (mainMenu.getActive()) {
                    std::cout << "Exit To Main Menu!" << std::endl;
                    _gameView.setView(ViewState::MENU);
                }
            }
        }

        void update() {
            title.update();
            mainMenu.update();
        }

        void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>>) override {
            title.draw();
            mainMenu.draw();
            handleInput();
        }

    private:
        TextBox title;
        TextBox mainMenu;
        GameView &_gameView;

        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
