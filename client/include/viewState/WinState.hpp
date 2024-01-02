/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** WinState.hpp
*/

#pragma once
#include "IDraw.hpp"
#include "../graphicalComponents/RectBox.hpp"
#include "../graphicalComponents/TextBox.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace RType {
    /**
     * @class WinState
     * @brief Represents a state where entities are not drawn.
     */
    class WinState : public IDraw {
    public:
        /**
         * @brief Constructor for WinState.
         * @param window The SFML RenderWindow.
         * @param gameView The GameView associated with the state.
         */
        WinState(sf::RenderWindow &window, GameView &gameView, IGraphicalModule *graphicalModule)
            : _gameView(gameView), _graphicalModule(graphicalModule),
              backgroundRect(window, sf::Vector2f(((((window.getSize().x - 450) / 2))), ((window.getSize().y - 400) / 2)), sf::Vector2f(450.0f, 400.0f), sf::Color::Black, sf::Color::Magenta, 5.0f),
              wonText(window, sf::Color::Magenta, 30, ((((window.getSize().x - 450) / 2))) + 150, ((window.getSize().y - 400) / 2) + 15, "You Won!"),
              hpText(window, sf::Color::Magenta, 20, ((((window.getSize().x - 450) / 2))) + 200, ((window.getSize().y - 400) / 2) + 115, ""),
              scoreText(window, sf::Color::Magenta, 20, ((((window.getSize().x - 450) / 2))) + 200, ((window.getSize().y - 400) / 2) + 215, ""),
              exitText(window, sf::Color::Magenta, 20, ((((window.getSize().x - 450) / 2))) + 200, ((window.getSize().y - 400) / 2) + 315, "Exit") {}

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
            backgroundRect.draw(_graphicalModule);
            wonText.draw(_graphicalModule);
            hpText.draw(_graphicalModule);
            scoreText.draw(_graphicalModule);
            exitText.draw(_graphicalModule);
            handleInput();

            std::shared_ptr<AGraphicEntity> player = _gameView.getGraphicEntityByName("playerStarship");
            if (player != nullptr && player->getEntity()->getComponent<PlayerComponent>()) {
                float health = player->getEntity()->getComponent<HealthComponent>()->getHealth();
                std::ostringstream healthString; healthString << std::fixed << std::setprecision(0) << health;
                hpText.setText("Health " + healthString.str());
                float score = player->getEntity()->getComponent<PlayerComponent>()->getScore();
                std::ostringstream scoreString; scoreString << std::fixed << std::setprecision(0) << score;
                scoreText.setText("Score " + scoreString.str());
            } else hpText.setText("Player entity not found");
        }

    private:
        GameView &_gameView; /**< The associated GameView. */
        RectBox backgroundRect; /**< Rectangle of background. */
        TextBox wonText; /**< Text "You won!". */
        TextBox hpText; /**< Text "hp". */
        TextBox scoreText; /**< Text "pts". */
        TextBox exitText; /**< Exit Text. */
        IGraphicalModule *_graphicalModule;

        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
