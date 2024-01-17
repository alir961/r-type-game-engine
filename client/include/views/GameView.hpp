/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "IView.hpp"
#include "../components/ClickableText.hpp"
#include "../components/Background.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <utility>

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
        explicit GameView(std::string username): _username(std::move(username)) {}

        void update() override {}

        /**
         * @brief Draws entities on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw entities.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(std::vector<GraphicEntityPtr> graphicEntities) override {
            /*const GraphicEntityPtr player = getPlayerEntity();
            const EntityPtr &playerEntity = (player == nullptr) ? nullptr : player->getEntity();*/
            const float deltaTime = _clock.restart().asSeconds();

            _background.update(deltaTime);
            _background.draw();
            //_playerNameText.draw();
            //_healthBarText.draw();
            //_scoreText.draw();

            /*if (player != nullptr && playerEntity->getComponent<PlayerComponent>()) {
                const int health = playerEntity->getComponent<HealthComponent>()->getHealth();
                const int score = playerEntity->getComponent<PlayerComponent>()->getScore();

                _healthBarText.setText("Health " + std::to_string(health));
                _scoreText.setText("Score " + std::to_string(score));
                _playerNameText.setText(_username);
            } else {
                _healthBarText.setText("Health " + std::to_string(0));
                _scoreText.setText("Score " + std::to_string(0));
            }*/

            /*for (auto &entity: graphicEntities) {
                entity->draw();
            }*/
        }


    private:
        ClickableText _playerNameText = ClickableText(Color::Cyan, 20, 10.0f, 10.0f, ""); /**< Player Name Text. */
        ClickableText _healthBarText = ClickableText(Color::Cyan, 20, 10.0f, 40.0f, ""); /**< Health Text. */
        ClickableText _scoreText = ClickableText(Color::Cyan, 20, WINDOW_WIDTH - 200.0f, 10.0f, ""); /**< Score Text. */
        Background _background = Background({"client/assets/background/1.png",
                                             "client/assets/background/2.png",
                                             "client/assets/background/3.png",
                                             "client/assets/background/4.png"},
                                            {0.2F, 0.5F, 1.0F, 2.0F});
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        sf::Clock _clock;
        std::string _username;

    };
}
