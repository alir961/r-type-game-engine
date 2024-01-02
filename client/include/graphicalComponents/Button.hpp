/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

namespace RType {

    /**
     * @class Button
     * @brief Represents a simple clickable button using SFML.
     * @tparam width The width of the button.
     * @tparam height The height of the button.
     */
    template<int width, int height>
    class Button {
    private:
        sf::RenderWindow &_window; /**< The SFML RenderWindow where the text box will be drawn. */
        int _x; /**< X-coordinate of the button. */
        int _y; /**< Y-coordinate of the button. */
        std::string _text; /**< Text displayed on the button. */
        sf::RectangleShape _rectangle; /**< SFML RectangleShape representing the button. */

    public:
        /**
         * @brief Constructor for the Button class.
         * @param x The X-coordinate of the button.
         * @param y The Y-coordinate of the button.
         * @param text The text to be displayed on the button.
         */
        explicit Button(sf::RenderWindow &window, float x, float y, std::string text) : _window(window), _x(x), _y(y),
                                                          _text(std::move(text)) {
            _rectangle.setPosition(x, y);
            _rectangle.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
        }

        /**
         * @brief Draws the button on the SFML RenderWindow.
         */
        void draw() {
            bool mouseOver = _rectangle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(_window)));

            _rectangle.setFillColor(mouseOver ? sf::Color(200, 200, 200) : sf::Color(128, 128, 128));
            _window.draw(_rectangle);

            sf::Font font;
            if (font.loadFromFile("client/assets/ka1.ttf")) {
                sf::Text buttonText(_text, font, 20);
                buttonText.setPosition(_x + 20, _y + 10);
                buttonText.setFillColor(sf::Color::White);
                _window.draw(buttonText);
            }
        }

        /**
         * @brief Executes a function if the button is clicked.
         * @param function The function to execute.
         */
        void executeIfClicked(std::function<void()> function) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
            bool mouseOver = _rectangle.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
            bool mouseClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);

            if (mouseOver && mouseClick) {
                function();
            }
        }
    };

}
