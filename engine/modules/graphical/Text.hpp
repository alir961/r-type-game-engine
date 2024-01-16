/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "engine/modules/graphical/AText.hpp"

namespace RType {

    class Text : public AText {
    private:
        WindowPtr _window;

    public:
        Text(WindowPtr window) : AText(), _window(window) {};

        Text(WindowPtr window, const std::string &text) : AText(text), _window(window) {};

        void draw() {
            sf::Font font;
            sf::Text text = sf::Text();

            font.loadFromFile("client/assets/ka1.ttf");
            text.setCharacterSize(_size);
            text.setPosition(sf::Vector2f(_position.first, _position.second));
            text.setString(_text);
            text.setFont(font);
            _window->draw(text);
        }
    };

}
