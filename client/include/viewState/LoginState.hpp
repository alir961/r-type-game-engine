/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once
#include "IDraw.hpp"
#include "../graphicalComponents/TextBox.hpp"
#include "../graphicalComponents/NumberInput.hpp"
#include "../graphicalComponents/TextInput.hpp"
#include "../graphicalComponents/Button.hpp"

namespace RType {
    class GameView;
    enum class ViewState;
    using LoginButton = Button<200, 40>;

    /**
     * @class LoginState
     * @brief Represents a login state with input box for user interaction.
     */
    class LoginState : public IDraw {
    public:
        /**
         * @brief Constructor for MenuState.
         * @param window The SFML RenderWindow.
         * @param gameView The GameView associated with the state.
         */
        LoginState(sf::RenderWindow &window, GameView &gameView, GraphicalModule *graphicalModule)
            : _window(window), _graphicalModule(graphicalModule), _gameView(gameView),
              portBoxTitle(window, sf::Color::Cyan, 20, 800.0f, 300.0f, "Port"),
              userNameBoxTitle(window, sf::Color::Cyan, 20, 800.0f, 400.0f, "User Name"),
              portBoxInput(window, 800.0f, 340.0f), userNameBoxInput(window, 800.0f, 440.0f) {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            loginButton.executeIfClicked([this] {
                _gameView.setView(ViewState::MENU);
            });
        }

        /**
         * @brief Updates the menu state.
         */
        void update() {
            portBoxInput.update(_gameView.getEvent());
            userNameBoxInput.update(_gameView.getEvent());
        }

        /**
         * @brief Draws the menu on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the menu.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow& window, std::vector<std::shared_ptr<RType::AGraphicEntity>>) override {
            portBoxTitle.draw(_graphicalModule);
            userNameBoxTitle.draw(_graphicalModule);
            portBoxInput.draw(_graphicalModule);
            userNameBoxInput.draw(_graphicalModule);
            loginButton.draw(_graphicalModule);
            handleInput();
        }

    private:
        GameView &_gameView; /**< The associated GameView. */
        sf::RenderWindow &_window; /**< The SFML RenderWindow. */
        TextBox portBoxTitle; /**< TextBox for Port of the game server. */
        TextBox userNameBoxTitle; /**< TextBox for UserName options. */
        NumberInput portBoxInput; /**< TextBoxInput for Port of the game server. */
        TextInput userNameBoxInput; /**< TextBoxInput for UserName options. */
        LoginButton loginButton = LoginButton(_window, 800, 500, "Login"); /**< Button for Log-in the game. */
        GraphicalModule *_graphicalModule;

        /**
         * @brief Checks if the left mouse button is clicked.
         * @return True if the left mouse button is clicked, false otherwise.
         */
        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
