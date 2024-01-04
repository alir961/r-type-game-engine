/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeadView.hpp
*/

#pragma once

#include "../components/RectBox.hpp"
#include "../components/TextBox.hpp"
#include "IView.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace RType {

    /**
     * @class DeadView
     * @brief Represents a state where entities are not drawn.
     */
    class DeadView : public IView {
    public:
        /**
         * @brief Constructor for DeadView.
         * @param window The SFML RenderWindow.
         * @param gameView The ClientViewport associated with the state.
         */
        DeadView(sf::RenderWindow &window, ClientViewport &gameView, IGraphicalModule *graphicalModule, ModuleProvider &provider)
            : _viewport(gameView), _graphicalModule(graphicalModule), _provider(provider),
              backgroundRect(window, sf::Vector2f(((((window.getSize().x - 450) / 2))), ((window.getSize().y - 400) / 2)), sf::Vector2f(450.0f, 400.0f), sf::Color::Black, sf::Color::Magenta, 5.0f),
              loseText(window, sf::Color::Magenta, 30, ((((window.getSize().x - 450) / 2))) + 150, ((window.getSize().y - 400) / 2) + 15, "You Lose!"),
              hpText(window, sf::Color::Magenta, 20, ((((window.getSize().x - 450) / 2))) + 200, ((window.getSize().y - 400) / 2) + 115, ""),
              scoreText(window, sf::Color::Magenta, 20, ((((window.getSize().x - 450) / 2))) + 200, ((window.getSize().y - 400) / 2) + 215, ""),
              exitText(window, sf::Color::Magenta, 20, ((((window.getSize().x - 450) / 2))) + 200, ((window.getSize().y - 400) / 2) + 315, "Exit") {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            exitText.handleInput();

            if (!isMouseClicked())
                return;
            if (exitText.getActive()) {
                std::cout << "Exit To Main Menu!\n";
                _viewport.setView(ViewState::MENU);
            }
        }

        /**
         * @brief Updates the menu state.
         */
        void update() override {
            exitText.update();
        }

        /**
         * @brief Draws entities on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw entities.
         * @param entities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow &window, std::vector<GraphicEntityPtr> entities) override {
            const GraphicEntityPtr player = _viewport.getGraphicEntityByName("playerStarship");
            const EntityPtr entity = player->getEntity();

            backgroundRect.draw(_graphicalModule);
            loseText.draw(_graphicalModule);
            hpText.draw(_graphicalModule);
            scoreText.draw(_graphicalModule);
            exitText.draw(_graphicalModule);
            handleInput();

            if (player != nullptr && entity->getComponent<PlayerComponent>()) {
                const int health = entity->getComponent<HealthComponent>()->getHealth();
                const int score = entity->getComponent<PlayerComponent>()->getScore();

                hpText.setText("Health " + std::to_string(health));
                scoreText.setText("Score " + std::to_string(score));
            } else hpText.setText("Player entity not found");
        }

    private:
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        RectBox backgroundRect; /**< Rectangle of background. */
        TextBox loseText; /**< Text "You Lose!". */
        TextBox hpText; /**< Text "hp". */
        TextBox scoreText; /**< Text "pts". */
        TextBox exitText; /**< Exit Text. */
        IGraphicalModule *_graphicalModule;
        ModuleProvider &_provider;

        static bool isMouseClicked() {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
