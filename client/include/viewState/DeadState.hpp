/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeadState.hpp
*/

#pragma once
#include "IDraw.hpp"
#include "../graphicalComponents/RectBox.hpp"
#include "../graphicalComponents/TextBox.hpp"

namespace RType {
    /**
     * @class DeadState
     * @brief Represents a state where entities are not drawn.
     */
    class DeadState : public IDraw {
    public:
        /**
         * @brief Constructor for DeadState.
         * @param window The SFML RenderWindow.
         * @param gameView The GameView associated with the state.
         */
        DeadState(sf::RenderWindow &window, GameView &gameView)
            : _gameView(gameView),
              backgroundRect(window, sf::Vector2f(((((window.getSize().x - 450) / 2))), ((window.getSize().y - 400) / 2)), sf::Vector2f(450.0f, 400.0f), sf::Color::Black, sf::Color::Magenta, 5.0f),
              loseText(window, sf::Color::Magenta, 30, ((((window.getSize().x - 450) / 2))) + 150, ((window.getSize().y - 400) / 2) + 15, "You Lose!"),
              hpText(window, sf::Color::Magenta, 20, ((((window.getSize().x - 450) / 2))) + 200, ((window.getSize().y - 400) / 2) + 115, "100hp"),
              pointsText(window, sf::Color::Magenta, 20, ((((window.getSize().x - 450) / 2))) + 200, ((window.getSize().y - 400) / 2) + 215, "500pts"),
              exitText(window, sf::Color::White, 20, ((((window.getSize().x - 450) / 2))) + 200, ((window.getSize().y - 400) / 2) + 315, "Exit") {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            exitText.handleInput();

            if (isMouseClicked()) {
                if (exitText.getActive()) {
                    std::cout << "Exit To Main Menu!" << std::endl;
                    _gameView.setView(ViewState::MENU);
                }
            }
        }

        /**
         * @brief Updates the menu state.
         */
        void update() {
            exitText.update();
        }

        /**
         * @brief Draws entities on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw entities.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>> graphicEntities) override {
            backgroundRect.draw();
            loseText.draw();
            hpText.draw();
            pointsText.draw();
            exitText.draw();
            handleInput();
        }

    private:
        GameView &_gameView; /**< The associated GameView. */
        RectBox backgroundRect; /**< Rectangle of background. */
        TextBox loseText; /**< Text "You Lose!". */
        TextBox hpText; /**< Text "hp". */
        TextBox pointsText; /**< Text "pts". */
        TextBox exitText; /**< Exit Text. */

        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
