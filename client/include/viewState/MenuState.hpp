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

    class MenuState : public IDraw {
    public:
        MenuState(sf::RenderWindow &window, GameView &gameView)
            : _window(window), startBox(window, sf::Color::Cyan, 100.0f, 200.0f, "Start"),
              optionsBox(window, sf::Color::Cyan, 100.0f, 250.0f, "Options"),
              quitBox(window, sf::Color::Cyan, 100.0f, 300.0f, "Quit"), _gameView(gameView) {}

        void handleInput() {
            startBox.handleInput();
            optionsBox.handleInput();
            quitBox.handleInput();

            if (isMouseClicked()) {
                if (startBox.getActive()) {
                    std::cout << "Start Game!" << std::endl;
                    _gameView.setView(ViewState::GAME);
                } else if (optionsBox.getActive()) {
                    std::cout << "Options Selected!" << std::endl;
                    _gameView.setView(ViewState::OPTIONS);
                } else if (quitBox.getActive()) {
                    std::cout << "Quit Game!" << std::endl;
                    _window.close();
                }
            }
        }

        void update() {
            startBox.update();
            optionsBox.update();
            quitBox.update();
        }

        void draw(sf::RenderWindow& window, std::vector<std::shared_ptr<RType::AGraphicEntity>>) override {
            startBox.draw();
            optionsBox.draw();
            quitBox.draw();
            handleInput();
        }

    private:
        TextBox startBox;
        TextBox optionsBox;
        TextBox quitBox;
        GameView &_gameView;
        sf::RenderWindow &_window;

        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
