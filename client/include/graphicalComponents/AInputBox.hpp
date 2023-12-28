/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

namespace RType {
    /**
     * @class AInputBox
     * @brief Abstract base class for input boxes in the RType game.
     */
    class AInputBox {
    public:
        /**
         * @brief Constructor for AInputBox.
         * @param x The x-coordinate of the input box.
         * @param y The y-coordinate of the input box.
         * @param maxChars The maximum number of characters the input box can hold.
         */
        explicit AInputBox(sf::RenderWindow &window, float x, float y, size_t maxChars) : _window(window), _x(x),
                                                                _y(y),
                                                                _maxChars(maxChars) {
            _rect.setSize(sf::Vector2f(_width, _height));
            _rect.setPosition(_x, _y);
            _rect.setOutlineThickness(2);
            _rect.setOutlineColor(sf::Color::Blue);

            _text.setFont(_font);
            _text.setCharacterSize(_fontSize);
            _text.setFillColor(sf::Color::White);
        }

        /**
         * @brief Virtual destructor for AInputBox.
         */
        virtual ~AInputBox() = default;

        /**
         * @brief Abstract method for updating the input box.
         * @param window The SFML RenderWindow for updating the input box.
         */
        virtual void update() = 0;

        /**
         * @brief Draws the input box on the SFML RenderWindow.
         * @param window The SFML RenderWindow to draw the input box on.
         */
        void draw() {
            _window.draw(_rect);

            _text.setString(_textStr);
            _text.setPosition(_x + 5, _y + 5);
            _window.draw(_text);
        }

        /**
         * @brief Checks if the input box is currently active.
         * @return True if the input box is active, false otherwise.
         */
        [[nodiscard]] bool isActive() const {
            return _active;
        }

        sf::RenderWindow &_window; /**< The SFML RenderWindow where the text box will be drawn. */
        float _x; /**< The x-coordinate of the input box. */
        float _y; /**< The y-coordinate of the input box. */
        float _width = 200; /**< The width of the input box. */
        float _height = 40; /**< The height of the input box. */
        int _fontSize = 20; /**< The font size of the text in the input box. */
        size_t _maxChars; /**< The maximum number of characters the input box can hold. */
        bool _active = false; /**< Flag indicating whether the input box is currently active. */
        std::string _textStr; /**< The text content of the input box. */
        sf::RectangleShape _rect; /**< SFML RectangleShape representing the input box. */
        sf::Font _font; /**< SFML Font for the text in the input box. */
        sf::Text _text; /**< SFML Text object for rendering text in the input box. */
    };
}
