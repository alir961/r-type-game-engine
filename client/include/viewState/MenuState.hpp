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
    /**
     * @class MenuState
     * @brief Represents a state with a menu for user interaction.
     */
    class MenuState : public IDraw {
    public:
        /**
         * @brief Constructor for MenuState.
         * @param window The SFML RenderWindow.
         * @param gameView The GameView associated with the state.
         */
        MenuState(sf::RenderWindow &window, GameView &gameView, IGraphicalModule *graphicalModule)
            : _window(window), _graphicalModule(graphicalModule), _gameView(gameView),
              titleBox(window, sf::Color::Cyan, 30, window.getSize().x / 2.0f, 50.0f, "R Type"),
              startBox(window, sf::Color::Cyan, 20, 100.0f, 200.0f, "Start"),
              optionsBox(window, sf::Color::Cyan, 20, 100.0f, 250.0f, "Options"),
              quitBox(window, sf::Color::Cyan, 20, 100.0f, 300.0f, "Quit") {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            titleBox.handleInput();
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

        /**
         * @brief Updates the menu state.
         */
        void update() {
            startBox.update();
            optionsBox.update();
            quitBox.update();
        }

        /**
         * @brief Draws the menu on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the menu.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow& window, std::vector<std::shared_ptr<RType::AGraphicEntity>>) override {
            titleBox.draw(_graphicalModule);
            startBox.draw(_graphicalModule);
            optionsBox.draw(_graphicalModule);
            quitBox.draw(_graphicalModule);
            handleInput();
        }

    private:
        TextBox titleBox; /**< TextBox for the game title. */
        TextBox startBox; /**< TextBox for starting the game. */
        TextBox optionsBox; /**< TextBox for accessing options. */
        TextBox quitBox; /**< TextBox for quitting the game. */
        GameView &_gameView; /**< The associated GameView. */
        sf::RenderWindow &_window; /**< The SFML RenderWindow. */
        IGraphicalModule *_graphicalModule;

        /**
         * @brief Checks if the left mouse button is clicked.
         * @return True if the left mouse button is clicked, false otherwise.
         */
        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
