/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "../components/ClickableText.hpp"
#include "IView.hpp"

namespace RType {

    /**
     * @brief Represents the pause menu state in the game.
     *
     * This class provides functionality for handling user input, updating the state,
     * and drawing elements related to the pause menu.
     */
    class PauseView : public IView {
    public:
        /**
         * @brief Constructs the PauseView.
         *
         * @param window Reference to the SFML render window.
         * @param gameView Reference to the ClientViewport.
         */
        explicit PauseView(ClientViewport &gameView) : _viewport(gameView) {}

        /**
         * @brief Handles user input for the pause menu.
         */
        void handleInput() {
            _title.handleInput();
            _mainMenu.handleInput();
            _resume.handleInput();
            _options.handleInput();

            if (_module->isMouseClicked()) {
                if (_mainMenu.isClicked()) {
                    _logger->debug("Return to menu from pause");
                    _viewport.setView(ViewState::MENU);
                }
                if (_resume.isClicked()) {
                    _logger->debug("Return to game from pause");
                    _viewport.setView(ViewState::GAME);
                }
                if (_options.isClicked()) {
                    _logger->debug("Open options from pause");
                    _viewport.setView(ViewState::OPTIONSGAME);
                }
            }
        }

        /**
         * @brief Updates the pause menu state.
         */
        void update() override {
            _mainMenu.update();
            _resume.update();
            _options.update();
        }

        /**
         * @brief Draws elements of the pause menu on the screen.
         *
         * @param window Reference to the SFML render window.
         * @param entities A vector of shared pointers to graphic entities.
         */
        void draw(std::vector<GraphicEntityPtr>) override {
            _title.draw();
            _mainMenu.draw();
            _resume.draw();
            _options.draw();
            handleInput();
        }

    private:
        ClickableText _title = ClickableText(Color::Cyan, 30, WINDOW_WIDTH / 2.0F, 50.0F, "Pause"); /**< ClickableText for the title. */
        ClickableText _resume = ClickableText(Color::Cyan, 20, 500.0F, 195.0F, "Resume"); /**< ClickableText for resume. */
        ClickableText _options = ClickableText(Color::Cyan, 20, 500.0F, 245.0F, "Options"); /**< ClickableText to go options. */
        ClickableText _mainMenu = ClickableText(Color::Cyan, 20, 500.0F, 295.0F, "Exit To Main Menu"); /**< ClickableText for the menu. */
        ClientViewport &_viewport; /**< Reference to the ClientViewport. */
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
    };
}
