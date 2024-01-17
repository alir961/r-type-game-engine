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
#include "engine/modules/ModuleProvider.hpp"
#include "engine/modules/logger/ILoggerModule.hpp"

namespace RType {

    class Sprite : public ASprite {
    private:
        WindowPtr _window;
        sf::Texture _texture;
        sf::Sprite _sprite;
        ILoggerModule *_logger = ModuleProvider::getInstance()->get<ILoggerModule>(ModuleType::LOGGER);

    public:
        Sprite(WindowPtr window, std::string texturePath) : ASprite(std::move(texturePath)),
                                                            _window(std::move(window)) {
            if (!_texture.loadFromFile(_texturePath))
                throw ModuleException("Unable to load texture '" + _texturePath + "'");
            _sprite = sf::Sprite(_texture);
            _logger->debug("Load sprite " + _texturePath);
        };

        void draw() override {
            _sprite.setPosition(_position.first, _position.second);
            _sprite.setScale(sf::Vector2f(_scale.first, _scale.second));
            _sprite.setOrigin(sf::Vector2f(_origin.first, _origin.second));
            _sprite.setRotation(_rotation);
            _window->draw(_sprite);
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