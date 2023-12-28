/*
** EPITECH PROJECT, 2023
** zappy
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
         * @param x The x-coordinate of the input box.
         * @param y The y-coordinate of the input box.
         * @param defaultValue The default text value.
         */
        TextInput(int x, int y, const std::string &defaultValue = "") : AInputBox(x, y, 15) {
            _textStr = defaultValue;
        }

        /**
         * @brief Updates the TextInput based on user input.
         * @param window The SFML RenderWindow for updating the input box.
         */
        void update(sf::RenderWindow& window) override {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                _active = _rect.getGlobalBounds().contains(
                        static_cast<float>(sf::Mouse::getPosition(window).x),
                        static_cast<float>(sf::Mouse::getPosition(window).y)
                );

            if (!_active) return;

            for (int i = 32; i <= 122; ++i) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i)) && _textStr.size() < _maxChars)
                    _textStr += static_cast<char>(tolower(i));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !_textStr.empty())
                _textStr.pop_back();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                std::cout << "Text: " << getValue() << std::endl;
            }
        }

        /**
         * @brief Gets the text entered in the input box.
         * @return The text value.
         */
        [[nodiscard]] const std::string &getValue() const {
            return _textStr;
        }
    };

}
