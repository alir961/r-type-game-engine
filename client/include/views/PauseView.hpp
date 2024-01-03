/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "IView.hpp"
#include "../components/TextBox.hpp"

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
        PauseView(sf::RenderWindow &window, ClientViewport &gameView, IGraphicalModule *graphicalModule)
            : _graphicalModule(graphicalModule), _viewport(gameView),
              title(window, sf::Color::Cyan, 30, window.getSize().x / 2.0f, 50.0f, "Pause"),
              resume(window, sf::Color::Cyan, 20, 500.0f, 195.0f, "Resume"),
              mainMenu(window, sf::Color::Cyan, 20, 500.0f, 245.0f, "Exit To Main Menu") {}

        /**
         * @brief Handles user input for the pause menu.
         */
        void handleInput() {
            title.handleInput();
            mainMenu.handleInput();
            resume.handleInput();

            if (isMouseClicked()) {
                if (mainMenu.getActive()) {
                    std::cout << "Exit To Main Menu!" << std::endl;
                    _viewport.setView(ViewState::MENU);
                }
                if (resume.getActive()) {
                    std::cout << "Resume Game!" << std::endl;
                    _viewport.setView(ViewState::GAME);
                }
            }
        }

        /**
         * @brief Updates the pause menu state.
         */
        void update() override {
            mainMenu.update();
            resume.update();
        }

        /**
         * @brief Draws elements of the pause menu on the screen.
         *
         * @param window Reference to the SFML render window.
         * @param entities A vector of shared pointers to graphic entities.
         */
        void draw(sf::RenderWindow &window, std::vector<GraphicEntityPtr>) override {
            title.draw(_graphicalModule);
            mainMenu.draw(_graphicalModule);
            resume.draw(_graphicalModule);
            handleInput();
        }

    private:
        TextBox title; /**< TextBox for the title. */
        TextBox mainMenu; /**< TextBox for the menu. */
        TextBox resume; /**< TextBox for resume. */
        ClientViewport &_viewport; /**< Reference to the ClientViewport. */
        IGraphicalModule *_graphicalModule;

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
