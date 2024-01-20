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
         */
        TextInput(int x, int y) : AInputBox(x, y, 15) {}

        /**
         * @brief Constructor for TextInput.
         * @param window Reference to the SFML RenderWindow.
         * @param x X-coordinate of the input box.
         * @param y Y-coordinate of the input box.
         * @param defaultValue Default value for the input box (optional, defaults to an empty string).
         */
        TextInput(int x, int y, const std::string &defaultValue) : AInputBox(x, y, 15) {
            _text = defaultValue;
        }

        /**
         * @brief Get the text value entered in the input box.
         * @return The text value.
         */
        [[nodiscard]] const std::string &getValue() const {
            return _text;
        }

        void setText(std::string value) override {
            _text = value;
            _textDisplay->setText(value);
        }

    private:
        /**
         * @brief Check if the input character is a valid alphabet input.
         * @param inputChar The input character to check.
         * @return True if the character is an alphabet letter, false otherwise.
         */
        [[nodiscard]] bool isValidInput(char inputChar) override {
            return (std::isprint(inputChar) != 0);
        }
    };
}
