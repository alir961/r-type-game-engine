/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeadView.hpp
*/

#pragma once

#include "../components/ClickableText.hpp"
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
    class WinDeadView : public IView {
    public:
        /**
         * @brief Constructor for DeadView.
         * @param window The SFML RenderWindow.
         * @param gameView The ClientViewport associated with the state.
         */
        WinDeadView(ClientViewport &gameView) : _viewport(gameView) {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            _exitText.handleInput();

            if (!(_module->isMouseClicked()))
                return;
            if (_exitText.isClicked()) {
                std::cout << "Exit To Main Menu!\n";
                _viewport.setView(ViewState::MENU);
            }
        }

        /**
         * @brief Updates the menu state.
         */
        void update() override {
            const GraphicEntityPtr player = getPlayerEntity();
            const EntityPtr &playerEntity = (player == nullptr) ? nullptr : player->getEntity();

            if (player != nullptr && playerEntity->getComponent<PlayerComponent>()) {
                const int score = playerEntity->getComponent<PlayerComponent>()->getScore();
                _scoreText.setText("Score " + std::to_string(score));
            }
            _exitText.update();
        }

        /**
         * @brief Draws entities on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw entities.
         * @param entities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(std::vector<GraphicEntityPtr> entities) override {
            _loseWinText.draw();
            _hpText.draw();
            _scoreText.draw();
            _exitText.draw();
            handleInput();
        }

    private:
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        ClickableText _loseWinText = ClickableText(Color::Magenta, 30, ((WINDOW_WIDTH - 450) / 2) + 150, ((WINDOW_HEIGHT - 400) / 2) + 15, "You are Dead !");
        ClickableText _hpText = ClickableText(Color::Magenta, 20, ((WINDOW_WIDTH - 450) / 2) + 200, ((WINDOW_HEIGHT - 400) / 2) + 115, "Health 0");
        ClickableText _scoreText = ClickableText(Color::Magenta, 20, ((WINDOW_WIDTH - 450) / 2) + 200, ((WINDOW_HEIGHT - 400) / 2) + 215, "");
        ClickableText _exitText = ClickableText(Color::Magenta, 20, ((WINDOW_WIDTH - 450) / 2) + 200, ((WINDOW_HEIGHT - 400) / 2) + 315, "Exit");
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        std::string _winOrLose;
    };
}
