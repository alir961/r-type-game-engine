/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "../components/TextBox.hpp"
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
                if (_mainMenu.isActive()) {
                    std::cout << "Exit To Main Menu!\n";
                    _viewport.setView(ViewState::MENU);
                }
                if (_resume.isActive()) {
                    std::cout << "Resume Game!\n";
                    _viewport.setView(ViewState::GAME);
                }
                if (_options.isActive()) {
                    std::cout << "Resume Game!\n";
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
        TextBox _title = TextBox(Color::Cyan, 30, WINDOW_WIDTH / 2.0F, 50.0F, "Pause"); /**< TextBox for the title. */
        TextBox _resume = TextBox(Color::Cyan, 20, 500.0F, 195.0F, "Resume"); /**< TextBox for resume. */
        TextBox _options = TextBox(Color::Cyan, 20, 500.0F, 245.0F, "Options"); /**< TextBox to go options. */
        TextBox _mainMenu = TextBox(Color::Cyan, 20, 500.0F, 295.0F, "Exit To Main Menu"); /**< TextBox for the menu. */
        ClientViewport &_viewport; /**< Reference to the ClientViewport. */
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
    };
}
