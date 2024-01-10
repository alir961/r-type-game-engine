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
    using LoginButton = Button<200, 40>;

    /**
     * @class LoginView
     * @brief Represents a login state with input box for user interaction.
     */
    class LoginView : public IView {
    public:
        /**
         * @brief Constructor for MenuView.
         * @param window The SFML RenderWindow.
         * @param gameView The ClientViewport associated with the state.
         */
        LoginView(sf::RenderWindow &window, ClientViewport &gameView, IGraphicalModule *graphicalModule, ModuleProvider &provider)
                : _viewport(gameView), _window(window), _graphicalModule(graphicalModule), _provider(provider),
              _portBoxTitle(window, sf::Color::Cyan, 20, 800.0f, 300.0f, "Port"),
              _userNameBoxTitle(window, sf::Color::Cyan, 20, 800.0f, 400.0f, "Username"),
              _portBoxInput(window, 800.0f, 340.0f),
              _userNameBoxInput(window, 800.0f, 440.0f) {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            if (_portBoxInput.getValue() != '\0'  && _userNameBoxInput.getValue() != "") {
                _loginButton.executeIfClicked([this] {
                    _viewport.connectToServer("127.0.0.1", _portBoxInput.getValue(), _userNameBoxInput.getValue());
                    _viewport.setView(ViewState::LOADSCREEN);
                });
            }
        }

        /**
         * @brief Updates the menu state.
         */
        void update() override {
            _portBoxInput.update(_viewport.getEvent());
            _userNameBoxInput.update(_viewport.getEvent());
        }

        /**
         * @brief Draws the menu on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the menu.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow &window, std::vector<GraphicEntityPtr> entities) override {
            _portBoxTitle.draw(_graphicalModule);
            _userNameBoxTitle.draw(_graphicalModule);
            _portBoxInput.draw(_graphicalModule);
            _userNameBoxInput.draw(_graphicalModule);
            _loginButton.draw(_graphicalModule);
            handleInput();
        }

    private:
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        sf::RenderWindow &_window; /**< The SFML RenderWindow. */
        TextBox _portBoxTitle; /**< TextBox for Port of the game server. */
        TextBox _userNameBoxTitle; /**< TextBox for UserName options. */
        NumberInput _portBoxInput; /**< TextBoxInput for Port of the game server. */
        TextInput _userNameBoxInput; /**< TextBoxInput for UserName options. */
        LoginButton _loginButton = LoginButton(_window, 800, 500, "Login"); /**< Button for Log-in the game. */
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
