/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** IGraphicEntity.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>

namespace RType {
    class TextBox {
    public:
        TextBox(sf::RenderWindow &window, const sf::Color &textColor, float x, float y, const std::string &initialText = "")
            : _window(window), textColor(textColor), isActive(false), isHovered(false) {
            font.loadFromFile("client/assets/ka1.ttf");
            text.setFont(font);
            text.setCharacterSize(20);
            text.setPosition(x, y);
            text.setString(initialText);
            text.setFillColor(textColor);
            updateText();
        }

        void handleInput() {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(_window));
                if (inputBoxBounds.contains(mousePosition)) {
                    setActive(true);
                } else {
                    setActive(false);
                }
            }
            sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(_window));
            isHovered = inputBoxBounds.contains(mousePosition);
        }

        void update() {
            if (isHovered) {
                text.setFillColor(sf::Color::Cyan);
            } else {
                text.setFillColor(sf::Color::Magenta);
            }
        }

        void draw() {
            _window.draw(text);
        }

        void setActive(bool active) {
            isActive = active;
        }

        bool getActive() const {
            return isActive;
        }

        const sf::Font &getFont() const {
            return font;
        }

    private:
        sf::RenderWindow &_window;
        sf::Color textColor;
        sf::Text text;
        sf::Font font;
        sf::FloatRect inputBoxBounds;
        bool isActive;
        bool isHovered;

        void updateText() {
            text.setString(text.getString());
            inputBoxBounds = text.getGlobalBounds();
        }
    };
}
