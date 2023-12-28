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
     * @class MenuState
     * @brief Represents a state with a menu for user interaction.
     */
    class LoginState : public IDraw {
    public:
        /**
         * @brief Constructor for MenuState.
         * @param window The SFML RenderWindow.
         * @param gameView The GameView associated with the state.
         */
        LoginState(sf::RenderWindow &window, GameView &gameView)
            : _window(window), portBoxTitle(window, sf::Color::Cyan, 20, 800.0f, 300.0f, "Port"),
              userNameBoxTitle(window, sf::Color::Cyan, 20, 800.0f, 400.0f, "User Name"),
              portBoxInput(window, 800.0f, 340.0f), userNameBoxInput(window, 800.0f, 440.0f),
              _gameView(gameView) {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            loginButton.executeIfClicked([this] {
                _gameView.setView(ViewState::GAME);
            });
        }

        /**
         * @brief Updates the menu state.
         */
        void update() {
            portBoxInput.update();
            userNameBoxInput.update();
        }

        /**
         * @brief Draws the menu on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the menu.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow& window, std::vector<std::shared_ptr<RType::AGraphicEntity>>) override {
            portBoxTitle.draw();
            userNameBoxTitle.draw();
            portBoxInput.draw();
            userNameBoxInput.draw();
            loginButton.draw();
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

        /**
         * @brief Checks if the left mouse button is clicked.
         * @return True if the left mouse button is clicked, false otherwise.
         */
        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
