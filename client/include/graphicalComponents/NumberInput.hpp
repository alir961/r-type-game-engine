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
     * @class NumberInput
     * @brief Represents an input box for numeric values.
     * @details Inherits from AInputBox for common input box functionality.
     */
    class NumberInput : public AInputBox {
    public:
        /**
         * @brief Constructor for NumberInput.
         * @param x The x-coordinate of the input box.
         * @param y The y-coordinate of the input box.
         * @param defaultValue The default numeric value.
         */
        NumberInput(int x, int y, int defaultValue = 0) : AInputBox(x, y, 5) {
            if (defaultValue != 0)
                _textStr = std::to_string(defaultValue);
            else
                _textStr = "";
        }

        /**
         * @brief Updates the NumberInput based on user input.
         * @param window The SFML RenderWindow for updating the input box.
         */
        void update(sf::RenderWindow& window) override {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                _active = _rect.getGlobalBounds().contains(
                        static_cast<float>(sf::Mouse::getPosition(window).x),
                        static_cast<float>(sf::Mouse::getPosition(window).y)
                );

            if (!_active) return;

            if (_textStr.size() < _maxChars) {
                for (int i = sf::Keyboard::Num0; i <= sf::Keyboard::Num9; ++i) {
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i))) continue;
                    auto digit = static_cast<char>(i - sf::Keyboard::Num0 + '0');
                    _textStr += digit;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !_textStr.empty())
                _textStr.pop_back();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                std::cout << "Value: " << getValue() << std::endl;
            }
        }

        /**
         * @brief Gets the numeric value entered in the input box.
         * @return The numeric value.
         */
        [[nodiscard]] int getValue() const {
            return std::atoi(_textStr.c_str());
        }
    };

}
