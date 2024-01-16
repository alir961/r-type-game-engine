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
     * @class TextInput
     * @brief Represents an input box for entering text.
     * @details Inherits from AInputBox for common input box functionality.
     */
    class TextInput : public AInputBox {
    public:
        /**
         * @brief Constructor for TextInput.
         * @param window Reference to the SFML RenderWindow.
         * @param x X-coordinate of the input box.
         * @param y Y-coordinate of the input box.
         * @param defaultValue Default value for the input box (optional, defaults to an empty string).
         */
        TextInput(int x, int y, const std::string &defaultValue = "") : AInputBox(x, y, 15) {
            _text = defaultValue;
        }

        /**
         * @brief Update function for handling events specific to TextInput.
         * Overrides the base class AInputBox's update function to handle text input.
         * @param event SFML Event to be processed.
         */
        void update(const sf::Event &event) override {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                //setActive(_box.getGlobalBounds().contains(mousePos));
            }
            if (_active) {
                if (event.type == sf::Event::TextEntered && !_keyPressed) {
                    char inputChar = static_cast<char>(event.text.unicode);
                    if (inputChar == '\b') {
                        if (!_text.empty()) {
                            _text.pop_back();
                            _keyPressed = true;
                        }
                    } else if (isValidInput(inputChar) && _text.size() < _maxChars) {
                        _text += std::tolower(inputChar);
                        _keyPressed = true;
                    }
                }
            }
            if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased) { _keyPressed = false; }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter && _active) { std::cout << _text << std::endl; }
            _textDisplay->setText(_text);
        }

        /**
         * @brief Get the text value entered in the input box.
         * @return The text value.
         */
        [[nodiscard]] const std::string &getValue() const {
            return _text;
        }

    private:
        bool _keyPressed{false}; /**< Flag indicating if a key is pressed. */

        /**
         * @brief Check if the input character is a valid alphabet input.
         * @param inputChar The input character to check.
         * @return True if the character is an alphabet letter, false otherwise.
         */
        bool isValidInput(char inputChar) const {
            return std::isprint(inputChar);
        }
    };
}
