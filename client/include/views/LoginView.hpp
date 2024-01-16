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
        explicit LoginView(ClientViewport &gameView) : _viewport(gameView) {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            if (_portBoxInput.getValue() != '\0' && !_usernameInput.getValue().empty() && !_hostnameInput.getValue().empty()) {
                _loginButton.executeIfClicked([this] {
                    _viewport.connectToServer(_hostnameInput.getValue(), _portBoxInput.getValue(), _usernameInput.getValue());
                    _viewport.setView(ViewState::LOADSCREEN);
                });
            }
        }

        /**
         * @brief Updates the menu state.
         */
        void update() override {
            _portBoxInput.update(_viewport.getEvent());
            _hostnameInput.update(_viewport.getEvent());
            _usernameInput.update(_viewport.getEvent());
        }

        /**
         * @brief Draws the menu on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the menu.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(std::vector<GraphicEntityPtr> entities) override {
            _portBoxTitle.draw();
            _hostnameTitle.draw();
            _usernameTitle.draw();
            _portBoxInput.draw(_module);
            _hostnameInput.draw(_module);
            _usernameInput.draw(_module);
            _loginButton.draw(_module);
            handleInput();
        }

    private:
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        TextBox _portBoxTitle = TextBox(sf::Color::Cyan, 20, 800.0F, 300.0F, "Port"); /**< TextBox for Port of the game server. */
        TextBox _usernameTitle = TextBox(sf::Color::Cyan, 20, 800.0f, 400.0f, "Hostname"); /**< TextBox for Hostname options. */
        TextBox _hostnameTitle = TextBox(sf::Color::Cyan, 20, 800.0F, 400.0F, "Username"); /**< TextBox for Username options. */
        NumberInput _portBoxInput = NumberInput(800.0F, 340.0F); /**< TextBoxInput for Port of the game server. */
        TextInput _hostnameInput = TextInput(800.0f, 440.0f); /**< TextBoxInput for Hostname options. */
        TextInput _usernameInput = TextInput(800.0F, 440.0F); /**< TextBoxInput for Username options. */
        LoginButton _loginButton = LoginButton(800, 500, "Login"); /**< Button for Log-in the game. */
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
    };
}
