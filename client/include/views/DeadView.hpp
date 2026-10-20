/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeadView.hpp
*/

#pragma once

#include "../components/Button.hpp"
#include "IView.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace RType {

    /**
     * @class DeadView
     * @brief Game over screen: final score, then play again or go back to the menu.
     */
    class WinDeadView : public IView {
    public:
        /**
         * @brief Constructor for DeadView.
         * @param gameView The ClientViewport associated with the state.
         */
        WinDeadView(ClientViewport &gameView)
                : _viewport(gameView),
                  _scoreText(std::to_string(gameView.getScore()), 80, Theme::Accent, Theme::CENTER_X, 500.0F, Align::CENTER),
                  _buttons(Theme::CENTER_X, 680.0F, {
                          {"Play again", [this] {
                              _logger->debug("Respawn from game over screen");
                              _viewport.setView(ViewState::GAME);
                          }},
                          {"Main menu", [this] {
                              _logger->debug("Exit to main menu from game over screen");
                              _viewport.setView(ViewState::MENU);
                          }},
                  }) {}

        void handleEvent(const sf::Event &event) override {
            _buttons.handleEvent(event);
        }

        /**
         * @brief Updates the game over state.
         */
        void update() override {
            _buttons.update();
        }

        /**
         * @brief Draws the game over screen over the frozen game.
         * @param entities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(std::vector<GraphicEntityPtr> entities) override {
            drawDimmedGame(entities);
            _title.draw();
            _subtitle.draw();
            _panel.draw();
            _scoreLabel.draw();
            _scoreText.draw();
            _buttons.draw();
        }

    private:
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        Label _title = Label("GAME OVER", 120, Theme::Danger, Theme::CENTER_X, 170.0F, Align::CENTER);
        Label _subtitle = Label("Your ship was destroyed", 32, Theme::TextDim, Theme::CENTER_X, 330.0F, Align::CENTER);
        Panel _panel = Panel(Theme::CENTER_X - 260.0F, 410.0F, 520.0F, 200.0F);
        Label _scoreLabel = Label("FINAL SCORE", 26, Theme::TextDim, Theme::CENTER_X, 440.0F, Align::CENTER);
        Label _scoreText;
        ButtonList _buttons;
    };
}
