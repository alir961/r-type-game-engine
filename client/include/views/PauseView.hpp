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
        PauseView(sf::RenderWindow &window, ClientViewport &gameView, IGraphicalModule *graphicalModule, ModuleProvider &provider)
            : _graphicalModule(graphicalModule), _viewport(gameView), _provider(provider),
              _title(window, sf::Color::Cyan, 30, window.getSize().x / 2.0f, 50.0f, "Pause"),
              _resume(window, sf::Color::Cyan, 20, 500.0f, 195.0f, "Resume"),
              _mainMenu(window, sf::Color::Cyan, 20, 500.0f, 245.0f, "Exit To Main Menu") {}

        /**
         * @brief Handles user input for the pause menu.
         */
        void handleInput() {
            _title.handleInput();
            _mainMenu.handleInput();
            _resume.handleInput();

            if (isMouseClicked()) {
                if (_mainMenu.getActive()) {
                    std::cout << "Exit To Main Menu!" << std::endl;
                    _viewport.setView(ViewState::MENU);
                }
                if (_resume.getActive()) {
                    std::cout << "Resume Game!" << std::endl;
                    _viewport.setView(ViewState::GAME);
                }
            }
        }

        /**
         * @brief Updates the pause menu state.
         */
        void update() override {
            _mainMenu.update();
            _resume.update();
        }

        /**
         * @brief Draws elements of the pause menu on the screen.
         *
         * @param window Reference to the SFML render window.
         * @param entities A vector of shared pointers to graphic entities.
         */
        void draw(sf::RenderWindow &window, std::vector<GraphicEntityPtr>) override {
            _title.draw(_graphicalModule);
            _mainMenu.draw(_graphicalModule);
            _resume.draw(_graphicalModule);
            handleInput();
        }

    private:
        TextBox _title; /**< TextBox for the title. */
        TextBox _mainMenu; /**< TextBox for the menu. */
        TextBox _resume; /**< TextBox for resume. */
        ClientViewport &_viewport; /**< Reference to the ClientViewport. */
        IGraphicalModule *_graphicalModule;
        ModuleProvider &_provider;

        /**
         * @brief Checks if the left mouse button is clicked.
         *
         * @return True if the left mouse button is clicked, false otherwise.
         */
        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
