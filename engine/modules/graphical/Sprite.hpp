/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <utility>

#include "engine/modules/graphical/ASprite.hpp"
#include "GraphicalModule.hpp"
#include "engine/exception/ModuleException.hpp"

namespace RType {

    class Sprite : public ASprite {
    private:
        WindowPtr _window;

    public:
        Sprite(WindowPtr window, std::string texturePath) : ASprite(std::move(texturePath)),
                                                            _window(std::move(window)) {};

        void draw() override {
            sf::Texture texture;
            sf::Sprite sprite;

            if (!texture.loadFromFile(_texturePath))
                throw ModuleException("Unable to load texture '" + _texturePath + "'");
            sprite = sf::Sprite(texture);
            sprite.setPosition(_position.first, _position.second);
            sprite.setScale(sf::Vector2f(_scale.first, _scale.second));
            sprite.setOrigin(sf::Vector2f(_origin.first, _origin.second));
            sprite.setRotation(_rotation);
            _window->draw(sprite);
        }

        RectFloat getGlobalBounds() override {
            sf::Texture texture;
            sf::Sprite sprite;
            sf::FloatRect bounds;

            if (!texture.loadFromFile(_texturePath))
                throw ModuleException("Unable to load texture '" + _texturePath + "'");
            sprite = sf::Sprite(texture);
            sprite.setPosition(_position.first, _position.second);
            sprite.setScale(sf::Vector2f(_scale.first, _scale.second));
            sprite.setOrigin(sf::Vector2f(_origin.first, _origin.second));
            sprite.setRotation(_rotation);
            bounds = sprite.getGlobalBounds();

            return (RectFloat) {
                    .left = bounds.left,
                    .top = bounds.top,
                    .width = bounds.width,
                    .height = bounds.height,
            };
        }
    };

}