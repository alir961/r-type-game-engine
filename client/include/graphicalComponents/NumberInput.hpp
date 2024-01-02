/*
** EPITECH PROJECT, 2023
** RType
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "AInputBox.hpp"

namespace RType {
    /**
     * @class NumberInput
     * @brief Represents an input box for entering numbers.
     * @details Inherits from AInputBox for common input box functionality.
     */
    class NumberInput : public AInputBox {
    public:
        /**
         * @brief Constructor for NumberInput.
         * @param window Reference to the SFML RenderWindow.
         * @param x X-coordinate of the input box.
         * @param y Y-coordinate of the input box.
         * @param defaultValue Default value for the input box (optional, defaults to 0).
         */
        NumberInput(sf::RenderWindow &window, int x, int y, int defaultValue = 0)
            : AInputBox(window, x, y, 15) {
            if (defaultValue != 0)
                _text = std::to_string(defaultValue);
            else
                _text = "";
        }

        /**
         * @brief Update function for handling events specific to NumberInput.
         * Overrides the base class AInputBox's update function to handle number input.
         * @param event SFML Event to be processed.
         */
        void update(const sf::Event &event) override {
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                setActive(_rect.getGlobalBounds().contains(mousePos));
            }

            if (_active) {
                if (event.type == sf::Event::TextEntered && !_keyPressed) {
                    char inputChar = static_cast<char>(event.text.unicode);
                    if (isValidInput(inputChar) && _text.size() < _maxChars) {
                        _text += static_cast<char>(event.text.unicode);
                        _keyPressed = true;
                    }
                } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::BackSpace) {
                    if (!_text.empty()) {
                        _text.pop_back();
                        _keyPressed = true;
                    }
                }
            }

            if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased) {
                _keyPressed = false;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter && _active) std::cout << _text << std::endl;
            _textDisplay.setString(_text);
        }

        /**
         * @brief Get the numerical value entered in the input box.
         * @return The numerical value.
         */
        [[nodiscard]] int getValue() const {
            return std::atoi(_text.c_str());
        }

    private:
        bool _keyPressed{false}; /**< Flag indicating if a key is pressed. */

        /**
         * @brief Check if the input character is a valid number input.
         * @param inputChar The input character to check.
         * @return True if the character is a digit or '.', false otherwise.
         */
        bool isValidInput(char inputChar) const {
            return std::isdigit(inputChar) || inputChar == '.';
        }
    };
}
