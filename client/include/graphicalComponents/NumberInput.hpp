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
        * @brief Represents an input box for entering number.
        * @details Inherits from AInputBox for common input box functionality.
        */
        class NumberInput : public AInputBox {
        public:
            NumberInput(sf::RenderWindow &window, int x, int y, int defaultValue = 0)
                : AInputBox(window, x, y, 5) {
                if (defaultValue != 0)
                    _text = std::to_string(defaultValue);
                else
                    _text = "";
            }

            void update(const sf::Event &event) override {
                if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    setActive(_rect.getGlobalBounds().contains(mousePos));
                }

                if (!_active) {
                    _keyPressed = false;
                    return;
                }

                if (event.type == sf::Event::TextEntered && !_keyPressed) {
                    if (_text.size() < _maxChars && std::isdigit(event.text.unicode)) {
                        _text += static_cast<char>(event.text.unicode);
                        _keyPressed = true;
                    }
                }

                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::BackSpace) {
                    if (!_text.empty()) {
                        _text.pop_back();
                        _keyPressed = false;
                    }
                }

                _textDisplay.setString(_text);
            }

            [[nodiscard]] int getValue() const {
                return std::atoi(_text.c_str());
            }

        private:
            bool _keyPressed{false};
        };

}
