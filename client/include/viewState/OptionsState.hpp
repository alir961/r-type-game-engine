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
     * @brief Represents the options menu state in the game.
     *
     * This class provides functionality for handling user input, updating the state,
     * and drawing elements related to the options menu.
     */
    class OptionsState : public IDraw {
    public:
        /**
         * @brief Constructs the OptionsState.
         *
         * @param window Reference to the SFML render window.
         * @param gameView Reference to the GameView.
         */
        OptionsState(sf::RenderWindow &window, GameView &gameView)
            : title(window, sf::Color::Cyan, 30, window.getSize().x / 2.0f, 50.0f, "Options"),
              mainMenu(window, sf::Color::Cyan, 20, 500.0f, 195.0f, "Exit To Main Menu"), _gameView(gameView) {}

        /**
         * @brief Handles user input for the options menu.
         */
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

        /**
         * @brief Updates the options menu state.
         */
        void update() {
            mainMenu.update();
        }

        /**
         * @brief Draws elements of the options menu on the screen.
         *
         * @param window Reference to the SFML render window.
         * @param entities A vector of shared pointers to graphic entities.
         */
        void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>>) override {
            title.draw();
            mainMenu.draw();
            handleInput();
        }

    private:
        TextBox title; /**< TextBox for the title. */
        TextBox mainMenu; /**< TextBox for the menu. */
        GameView &_gameView; /**< Reference to the GameView. */

        /**
         * @brief Checks if the left mouse button is clicked.
         *
         * @return True if the left mouse button is clicked, false otherwise.
         */
        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
