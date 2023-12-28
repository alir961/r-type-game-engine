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
        TextInput(sf::RenderWindow &window, int x, int y, const std::string &defaultValue = "")
            : AInputBox(window, x, y, 15) {
            _text = defaultValue;
        }

        void update(const sf::Event &event) override {
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                setActive(_rect.getGlobalBounds().contains(mousePos));
            }

            if (!_active) return;

            if (event.type == sf::Event::TextEntered) {
                if (_text.size() < _maxChars && event.text.unicode >= 32 && event.text.unicode <= 122) {
                    _text += static_cast<char>(std::tolower(event.text.unicode));
                }
            }

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::BackSpace) {
                if (!_text.empty()) _text.pop_back();
            }

            _textDisplay.setString(_text);
        }

        [[nodiscard]] const std::string &getValue() const {
            return _text;
        }
    };

}
