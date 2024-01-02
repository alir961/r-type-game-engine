/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once
#include "IDraw.hpp"
#include "../graphicalComponents/TextBox.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace RType {
    /**
     * @class GameState
     * @brief Represents a state where entities are drawn.
     */
    class GameState : public IDraw {
    public:
        /**
         * @brief Constructor for GameState.
         * @param window The SFML RenderWindow.
         * @param gameView The GameView associated with the state.
         */
        GameState(sf::RenderWindow &window, GameView &gameView, GraphicalModule *graphicalModule)
            : _gameView(gameView), _graphicalModule(graphicalModule),
              playerNameText(window, sf::Color::Cyan, 20, 10.0f, 10.0f, "PlayerName"),
              scoreText(window, sf::Color::Cyan, 20, window.getSize().x - 200.0f, 10.0f, ""),
              healthBarText(window, sf::Color::Cyan, 20, 10.0f, 40.0f, "") {
        }

        /**
         * @brief Draws entities on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw entities.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>> graphicEntities) override {
            playerNameText.draw(_graphicalModule);
            healthBarText.draw(_graphicalModule);
            scoreText.draw(_graphicalModule);

            std::shared_ptr<AGraphicEntity> player = _gameView.getGraphicEntityByName("playerStarship");
            if (player != nullptr && player->getEntity()->getComponent<PlayerComponent>()) {
                float health = player->getEntity()->getComponent<HealthComponent>()->getHealth();
                std::ostringstream healthString; healthString << std::fixed << std::setprecision(0) << health;
                healthBarText.setText("Health " + healthString.str());
                float score = player->getEntity()->getComponent<PlayerComponent>()->getScore();
                std::ostringstream scoreString; scoreString << std::fixed << std::setprecision(0) << score;
                scoreText.setText("Score " + scoreString.str());
            } else healthBarText.setText("Player entity not found");

            for (auto &entity: graphicEntities) {
                entity->draw(window);
            }
        }

    private:
        GameView &_gameView; /**< The associated GameView. */
        TextBox playerNameText; /**< Player Name Text. */
        TextBox healthBarText; /**< Health Text. */
        TextBox scoreText; /**< Score Text. */
        GraphicalModule *_graphicalModule;
    };
}
