/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "../../../engine/modules/graphical/GraphicalModule.hpp"
#include "../components/TextBox.hpp"
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
         * @param window The SFML RenderWindow.
         * @param gameView The ClientViewport associated with the state.
         */
        MenuView(sf::RenderWindow &window, ClientViewport &gameView, IGraphicalModule *graphicalModule, ModuleProvider &provider)
            : _window(window), _graphicalModule(graphicalModule), _viewport(gameView), _provider(provider),
              _titleBox(window, sf::Color::Cyan, 30, window.getSize().x / 2.0f, 50.0f, "R Type"),
              _startBox(window, sf::Color::Cyan, 20, 100.0f, 200.0f, "Start"),
              _optionsBox(window, sf::Color::Cyan, 20, 100.0f, 250.0f, "Options"),
              _quitBox(window, sf::Color::Cyan, 20, 100.0f, 300.0f, "Quit") {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            _titleBox.handleInput();
            _startBox.handleInput();
            _optionsBox.handleInput();
            _quitBox.handleInput();

            if (isMouseClicked()) {
                if (_startBox.getActive()) {
                    std::cout << "Start Game!\n";
                    _viewport.setView(ViewState::GAME);
                } else if (_optionsBox.getActive()) {
                    std::cout << "Options Selected!\n";
                    _viewport.setView(ViewState::OPTIONS);
                } else if (_quitBox.getActive()) {
                    std::cout << "Quit Game!\n";
                    _window.close();
                }
            }
        }

        /**
         * @brief Updates the menu state.
         */
        void update() override {
            _startBox.update();
            _optionsBox.update();
            _quitBox.update();
        }

        /**
         * @brief Draws the menu on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the menu.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow& window, std::vector<GraphicEntityPtr>) override {
            _titleBox.draw(_graphicalModule);
            _startBox.draw(_graphicalModule);
            _optionsBox.draw(_graphicalModule);
            _quitBox.draw(_graphicalModule);
            handleInput();
        }

    private:
        TextBox _titleBox; /**< TextBox for the game title. */
        TextBox _startBox; /**< TextBox for starting the game. */
        TextBox _optionsBox; /**< TextBox for accessing options. */
        TextBox _quitBox; /**< TextBox for quitting the game. */
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        sf::RenderWindow &_window; /**< The SFML RenderWindow. */
        IGraphicalModule *_graphicalModule;
        ModuleProvider &_provider;

        /**
         * @brief Checks if the left mouse button is clicked.
         * @return True if the left mouse button is clicked, false otherwise.
         */
        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
