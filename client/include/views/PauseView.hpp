/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "../components/Button.hpp"
#include "IView.hpp"

namespace RType {

    /**
     * @brief Represents the pause menu state in the game.
     *
     * The server keeps simulating while this menu is open (other players may still be playing).
     */
    class PauseView : public IView {
    public:
        /**
         * @brief Constructs the PauseView.
         *
         * @param gameView Reference to the ClientViewport.
         */
        explicit PauseView(ClientViewport &gameView)
                : _viewport(gameView),
                  _buttons(Theme::CENTER_X, 400.0F, {
                          {"Resume", [this] {
                              _logger->debug("Return to game from pause");
                              _viewport.setView(ViewState::GAME);
                          }},
                          {"How to play", [this] {
                              _logger->debug("Open the controls guide from pause");
                              _viewport.setView(ViewState::HOWTOPLAYGAME);
                          }},
                          {"Options", [this] {
                              _logger->debug("Open options from pause");
                              _viewport.setView(ViewState::OPTIONSGAME);
                          }},
                          {"Main menu", [this] {
                              _logger->debug("Return to menu from pause");
                              _viewport.setView(ViewState::MENU);
                          }},
                  }) {}

        /**
         * @brief Esc resumes, arrows + Enter pick an entry.
         */
        void handleEvent(const sf::Event &event) override {
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P)) {
                _viewport.setView(ViewState::GAME);
                return;
            }
            _buttons.handleEvent(event);
        }

        /**
         * @brief Updates the pause menu state.
         */
        void update() override {
            _buttons.update();
        }

        /**
         * @brief Draws the pause menu over the dimmed game.
         *
         * @param entities A vector of shared pointers to graphic entities.
         */
        void draw(std::vector<GraphicEntityPtr> entities) override {
            drawDimmedGame(entities);
            _panel.draw();
            _title.draw();
            _buttons.draw();
            _note.draw();
        }

    private:
        ClientViewport &_viewport; /**< Reference to the ClientViewport. */
        Panel _panel = Panel(Theme::CENTER_X - 320.0F, 230.0F, 640.0F, 590.0F);
        Label _title = Label("PAUSED", 64, Theme::Accent, Theme::CENTER_X, 262.0F, Align::CENTER);
        Label _note = Label("Online game: enemies and other players keep moving.   Esc to resume", 22, Theme::TextDim,
                            Theme::CENTER_X, 890.0F, Align::CENTER);
        ButtonList _buttons;
    };
}
