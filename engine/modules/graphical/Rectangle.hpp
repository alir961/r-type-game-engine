/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "engine/modules/graphical/ARectangle.hpp"
#include "GraphicalModule.hpp"

namespace RType {

    class Rectangle : public ARectangle {
    private:
        WindowPtr _window;

    public:
        explicit Rectangle(WindowPtr window) : _window(window) {};

        void draw() override {
            auto shape = sf::RectangleShape();

            shape.setPosition(_position.first, _position.second);
            shape.setSize(sf::Vector2f(_size.first, _size.second));
            shape.setFillColor(sf::Color{_backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a});
            shape.setOutlineColor(sf::Color{_outlineColor.r, _outlineColor.g, _outlineColor.b, _outlineColor.a});
            shape.setOutlineThickness(_outlineThickness);
            _window->draw(shape);
        }

        RectFloat getGlobalBounds() override {
            auto shape = sf::RectangleShape();

            shape.setPosition(_position.first, _position.second);
            shape.setSize(sf::Vector2f(_size.first, _size.second));
            shape.setFillColor(sf::Color{_backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a});
            shape.setOutlineColor(sf::Color{_outlineColor.r, _outlineColor.g, _outlineColor.b, _outlineColor.a});
            shape.setOutlineThickness(_outlineThickness);
            sf::FloatRect rect = shape.getGlobalBounds();

            return (RectFloat) {
                .left = rect.left,
                .top = rect.top,
                .width = rect.width,
                .height = rect.height,
            };
        }
    };

}