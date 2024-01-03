/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once
#include "IDraw.hpp"
#include "../graphicalComponents/TextBox.hpp"
#include "../graphicalComponents/Background.hpp"
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
        GameState(sf::RenderWindow &window, GameView &gameView, IGraphicalModule *graphicalModule)
            : _gameView(gameView), _graphicalModule(graphicalModule),
              playerNameText(window, sf::Color::Cyan, 20, 10.0f, 10.0f, "PlayerName"),
              scoreText(window, sf::Color::Cyan, 20, window.getSize().x - 200.0f, 10.0f, ""),
              healthBarText(window, sf::Color::Cyan, 20, 10.0f, 40.0f, ""),
              _background(window, {"client/assets/background/1.png",
                              "client/assets/background/2.png",
                              "client/assets/background/3.png",
                              "client/assets/background/4.png"},
                              { 0.2f, 0.5f, 1.0f, 2.0f }){
        }

        /**
         * @brief Draws entities on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw entities.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>> graphicEntities) override {
            float deltaTime = _clock.restart().asSeconds();
            _background.update(deltaTime);
            _background.draw(window);
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
                entity->draw(window, _graphicalModule);
            }
        }

    private:
        GameView &_gameView; /**< The associated GameView. */
        TextBox playerNameText; /**< Player Name Text. */
        TextBox healthBarText; /**< Health Text. */
        TextBox scoreText; /**< Score Text. */
        IGraphicalModule *_graphicalModule;
        Background _background;
        sf::Clock _clock;
    };
}
