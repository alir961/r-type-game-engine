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
                  portBoxTitle(window, sf::Color::Cyan, 20, 800.0f, 300.0f, "Port"),
                  userNameBoxTitle(window, sf::Color::Cyan, 20, 800.0f, 400.0f, "Username"),
                  portBoxInput(window, 800.0f, 340.0f),
                  userNameBoxInput(window, 800.0f, 440.0f) {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            loginButton.executeIfClicked([this] {
                _viewport.setView(ViewState::MENU);
            });
        }

        /**
         * @brief Updates the menu state.
         */
        void update() override {
            portBoxInput.update(_viewport.getEvent());
            userNameBoxInput.update(_viewport.getEvent());
        }

        /**
         * @brief Draws the menu on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the menu.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow &window, std::vector<GraphicEntityPtr> entities) override {
            portBoxTitle.draw(_graphicalModule);
            userNameBoxTitle.draw(_graphicalModule);
            portBoxInput.draw(_graphicalModule);
            userNameBoxInput.draw(_graphicalModule);
            loginButton.draw(_graphicalModule);
            handleInput();
        }

    private:
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        sf::RenderWindow &_window; /**< The SFML RenderWindow. */
        TextBox portBoxTitle; /**< TextBox for Port of the game server. */
        TextBox userNameBoxTitle; /**< TextBox for UserName options. */
        NumberInput portBoxInput; /**< TextBoxInput for Port of the game server. */
        TextInput userNameBoxInput; /**< TextBoxInput for UserName options. */
        LoginButton loginButton = LoginButton(_window, 800, 500, "Login"); /**< Button for Log-in the game. */
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
