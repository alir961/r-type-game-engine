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
         */
        NumberInput(int x, int y) : AInputBox(x, y, 15) {}

        /**
         * @brief Constructor for NumberInput.
         * @param window Reference to the SFML RenderWindow.
         * @param x X-coordinate of the input box.
         * @param y Y-coordinate of the input box.
         * @param defaultValue Default value for the input box (optional, defaults to 0).
         */
        NumberInput(int x, int y, int defaultValue) : AInputBox(x, y, 15) {
            _text = std::to_string(defaultValue);
        }

        /**
         * @brief Get the numerical value entered in the input box.
         * @return The numerical value.
         */
        [[nodiscard]] int getValue() const {
            return std::atoi(_text.c_str());
        }

        void setText(std::string value) override {
            _text = value;
            _textDisplay->setText(value);
        }

    private:
        /**
         * @brief Check if the input character is a valid number input.
         * @param inputChar The input character to check.
         * @return True if the character is a digit or '.', false otherwise.
         */
        [[nodiscard]] bool isValidInput(char inputChar) override {
            return (std::isdigit(inputChar) == 1) || inputChar == '.';
        }
    };

}
