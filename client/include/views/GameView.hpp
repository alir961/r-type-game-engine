/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "IView.hpp"
#include "../components/TextBox.hpp"
#include "../components/Background.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace RType {

    /**
     * @class GameView
     * @brief Represents a state where entities are drawn.
     */
    class GameView : public IView {
    public:
        /**
         * @brief Constructor for GameView.
         * @param window The SFML RenderWindow.
         * @param gameView The ClientViewport associated with the state.
         */
        GameView(sf::RenderWindow &window, ClientViewport &gameView, IGraphicalModule *graphicalModule, ModuleProvider &provider, std::string userName)
            : _viewport(gameView), _graphicalModule(graphicalModule), _provider(provider), _userName(userName),
              _playerNameText(window, sf::Color::Cyan, 20, 10.0f, 10.0f, ""),
              _scoreText(window, sf::Color::Cyan, 20, window.getSize().x - 200.0f, 10.0f, ""),
              _healthBarText(window, sf::Color::Cyan, 20, 10.0f, 40.0f, ""),
              _background(window, {"client/assets/background/1.png",
                              "client/assets/background/2.png",
                              "client/assets/background/3.png",
                              "client/assets/background/4.png"},
                              { 0.2F, 0.5F, 1.0F, 2.0F }){
        }

        void update() override {}

        /**
         * @brief Draws entities on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw entities.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow &window, std::vector<GraphicEntityPtr> graphicEntities) override {
            const GraphicEntityPtr player = _viewport.getGraphicEntityByName("playerStarship");
            const EntityPtr &playerEntity = player->getEntity();
            const float deltaTime = _clock.restart().asSeconds();

            _background.update(deltaTime);
            _background.draw(window);
            _playerNameText.draw(_graphicalModule);
            _healthBarText.draw(_graphicalModule);
            _scoreText.draw(_graphicalModule);

            if (player != nullptr && playerEntity->getComponent<PlayerComponent>()) {
                const int health = playerEntity->getComponent<HealthComponent>()->getHealth();
                const int score = playerEntity->getComponent<PlayerComponent>()->getScore();

                _healthBarText.setText("Health " + std::to_string(health));
                _scoreText.setText("Score " + std::to_string(score));
                _playerNameText.setText(_userName);
            } else
                _healthBarText.setText("Player playerEntity not found");

            for (auto &entity: graphicEntities) {
                entity->draw(window, _graphicalModule);
            }
        }

    private:
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        TextBox _playerNameText; /**< Player Name Text. */
        TextBox _healthBarText; /**< Health Text. */
        TextBox _scoreText; /**< Score Text. */
        IGraphicalModule *_graphicalModule;
        Background _background;
        sf::Clock _clock;
        ModuleProvider &_provider;
        std::string _userName;
    };
}
