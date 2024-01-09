/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "IView.hpp"
#include "../components/TextBox.hpp"
#include "../components/NumberInput.hpp"
#include "../components/TextInput.hpp"
#include "../components/Button.hpp"

namespace RType {

    enum class ViewState;

    /**
     * @class LoginView
     * @brief Represents a login state with input box for user interaction.
     */
    class LoadView : public IView {
    public:
        /**
         * @brief Constructor for MenuView.
         * @param window The SFML RenderWindow.
         * @param gameView The ClientViewport associated with the state.
         */
        LoadView(sf::RenderWindow &window, ClientViewport &gameView, IGraphicalModule *graphicalModule, UDPClientPtr client)
            : _window(window), _viewport(gameView), _graphicalModule(graphicalModule), _client(client),
              _loadingText(window, sf::Color::Magenta, 20, 250.0f, 300.0f, "Loading... if problem persist check server status and the port you provided and re launch"),
              _quitBox(window, sf::Color::Cyan, 20, 900.0f, 350.0f, "Quit") {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            _quitBox.handleInput();
            if (_client->getConnected())
                _viewport.setView(ViewState::MENU);
            if (_quitBox.getActive()) {
                std::cout << "Quit Game!\n";
                _viewport.closeConnectionToServer();
                _window.close();
                std::exit(0);
            }
        }

        /**
         * @brief Updates the menu state.
         */
        void update() override {
            _quitBox.update();
        }

        /**
         * @brief Draws the menu on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the menu.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow &window, std::vector<GraphicEntityPtr> entities) override {
            _loadingText.draw(_graphicalModule);
            _quitBox.draw(_graphicalModule);
            handleInput();
        }

    private:
        TextBox _quitBox; /**< TextBox for quitting the game. */
        sf::RenderWindow &_window; /**< The SFML RenderWindow. */
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        TextBox _loadingText; /**< TextBox for Port of the game server. */
        IGraphicalModule *_graphicalModule;
        UDPClientPtr _client;
    };
}
