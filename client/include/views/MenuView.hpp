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
     * @class MenuView
     * @brief Represents a state with a menu for user interaction.
     */
    class MenuView : public IView {
    public:
        /**
         * @brief Constructor for MenuView.
         * @param window The SFML RenderWindow.
         * @param gameView The ClientViewport associated with the state.
         */
        MenuView(sf::RenderWindow &window, ClientViewport &gameView, IGraphicalModule *graphicalModule)
            : _window(window), _graphicalModule(graphicalModule), _viewport(gameView),
              titleBox(window, sf::Color::Cyan, 30, window.getSize().x / 2.0f, 50.0f, "R Type"),
              startBox(window, sf::Color::Cyan, 20, 100.0f, 200.0f, "Start"),
              optionsBox(window, sf::Color::Cyan, 20, 100.0f, 250.0f, "Options"),
              quitBox(window, sf::Color::Cyan, 20, 100.0f, 300.0f, "Quit") {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            titleBox.handleInput();
            startBox.handleInput();
            optionsBox.handleInput();
            quitBox.handleInput();

            if (isMouseClicked()) {
                if (startBox.getActive()) {
                    std::cout << "Start Game!\n";
                    _viewport.setView(ViewState::GAME);
                } else if (optionsBox.getActive()) {
                    std::cout << "Options Selected!\n";
                    _viewport.setView(ViewState::OPTIONS);
                } else if (quitBox.getActive()) {
                    std::cout << "Quit Game!\n";
                    _window.close();
                }
            }
        }

        /**
         * @brief Updates the menu state.
         */
        void update() override {
            startBox.update();
            optionsBox.update();
            quitBox.update();
        }

        /**
         * @brief Draws the menu on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the menu.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow& window, std::vector<GraphicEntityPtr>) override {
            titleBox.draw(_graphicalModule);
            startBox.draw(_graphicalModule);
            optionsBox.draw(_graphicalModule);
            quitBox.draw(_graphicalModule);
            handleInput();
        }

    private:
        TextBox titleBox; /**< TextBox for the game title. */
        TextBox startBox; /**< TextBox for starting the game. */
        TextBox optionsBox; /**< TextBox for accessing options. */
        TextBox quitBox; /**< TextBox for quitting the game. */
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        sf::RenderWindow &_window; /**< The SFML RenderWindow. */
        IGraphicalModule *_graphicalModule;

        /**
         * @brief Checks if the left mouse button is clicked.
         * @return True if the left mouse button is clicked, false otherwise.
         */
        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
