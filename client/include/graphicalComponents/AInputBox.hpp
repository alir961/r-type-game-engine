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
        explicit AInputBox(sf::RenderWindow &window, int x, int y, size_t maxChars)
            : _x(x), _y(y), _maxChars(maxChars), _active(false), _window(window) {
            _rect.setSize(sf::Vector2f(200, 40));
            _rect.setPosition(x, y);
            _rect.setOutlineColor(sf::Color(200, 200, 200));
            _rect.setOutlineThickness(1);
            _rect.setFillColor(sf::Color::Transparent);
            _font.loadFromFile("client/assets/ka1.ttf");
            _textDisplay.setFont(_font);
            _textDisplay.setCharacterSize(20);
            _textDisplay.setPosition(x + 5, y + 5);
            _textDisplay.setFillColor(sf::Color::White);
        }

        virtual ~AInputBox() = default;

        virtual void update(const sf::Event &event) = 0;

        void draw() const {
            _window.draw(_rect);
            _window.draw(_textDisplay);
        }

        void setActive(bool active) {
            _active = active;
            _rect.setOutlineColor(active ? sf::Color::Blue : sf::Color(200, 200, 200));
        }

        [[nodiscard]] bool isActive() const {
            return _active;
        }

    protected:
        float _x;
        float _y;
        size_t _maxChars;
        bool _active;
        std::string _text;
        sf::RectangleShape _rect;
        sf::Text _textDisplay;
        sf::Font _font;
        sf::RenderWindow &_window;
    };
}
