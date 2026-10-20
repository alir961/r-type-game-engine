/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "engine/modules/graphical/IGraphicalModule.hpp"
#include "../components/Button.hpp"
#include "../components/TitleBanner.hpp"
#include "IView.hpp"

namespace RType {

    /**
     * @class MenuView
     * @brief Represents a state with a menu for user interaction.
     */
    class MenuView : public IView {
    public:
        /**
         * @brief Constructor for MenuView.
         * @param gameView The ClientViewport associated with the state.
         */
        explicit MenuView(ClientViewport &gameView)
                : _viewport(gameView),
                  _signedIn("Signed in as " + gameView.getUsername() + "  •  " + gameView.getServerAddress(), 24,
                            Theme::TextDim, Theme::CENTER_X, WINDOW_HEIGHT - 110.0F, Align::CENTER),
                  _buttons(Theme::CENTER_X, 470.0F, {
                          {"Play", [this] {
                              _logger->debug("Choose the difficulty from menu");
                              _viewport.setView(ViewState::DIFFICULTY);
                          }},
                          {"How to play", [this] {
                              _logger->debug("Open the controls guide from menu");
                              _viewport.setView(ViewState::HOWTOPLAY);
                          }},
                          {"Options", [this] {
                              _logger->debug("Go to options from menu");
                              _viewport.setView(ViewState::OPTIONS);
                          }},
                          {"Quit", [this] {
                              _logger->debug("Quit game from menu");
                              _viewport.closeConnectionToServer();
                              _module->close();
                          }},
                  }) {}

        void handleEvent(const sf::Event &event) override {
            _buttons.handleEvent(event);
        }

        /**
         * @brief Updates the menu state.
         */
        void update() override {
            _buttons.update();
        }

        /**
         * @brief Draws the menu.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(std::vector<GraphicEntityPtr>) override {
            _banner.draw();
            _buttons.draw();
            _signedIn.draw();
            _hint.draw();
        }

    private:
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        TitleBanner _banner = TitleBanner("Networked multiplayer shoot'em up");
        Label _signedIn;
        Label _hint = Label("First time? Open \"How to play\" to learn the controls.   ↑ ↓ + Enter or mouse to navigate",
                            22, Theme::TextDim, Theme::CENTER_X, WINDOW_HEIGHT - 70.0F, Align::CENTER);
        ButtonList _buttons;
    };
}
