/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <utility>

#include "engine/modules/graphical/AText.hpp"

namespace RType {

    class Text : public AText {
    private:
        WindowPtr _window;

    public:
        explicit Text(WindowPtr window) : _window(std::move(window)) {};

        Text(WindowPtr window, const std::string &text) : AText(text), _window(std::move(window)) {};

        void draw() override {
            sf::Font font;
            sf::Text text = sf::Text();

            font.loadFromFile("client/assets/ka1.ttf");
            text.setCharacterSize(_size);
            text.setPosition(sf::Vector2f(_position.first, _position.second));
            text.setString(_value);
            text.setFont(font);
            text.setFillColor(sf::Color(_color.r, _color.g, _color.b, _color.a));
            _window->draw(text);
        }
    };

}
