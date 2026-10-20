/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <unordered_map>
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
        sf::Sprite _sprite;
        ILoggerModule *_logger = ModuleProvider::getInstance()->get<ILoggerModule>(ModuleType::LOGGER);

        /**
         * @brief Load each texture file once: every bullet and enemy shares it.
         */
        const sf::Texture &getTexture(const std::string &path) {
            static std::unordered_map<std::string, sf::Texture> textures;
            auto iterator = textures.find(path);

            if (iterator != textures.end())
                return iterator->second;
            sf::Texture texture;
            if (!texture.loadFromFile(path))
                throw ModuleException("Unable to load texture '" + path + "'");
            _logger->debug("Load texture " + path);
            return textures.try_emplace(path, std::move(texture)).first->second;
        }

    public:
        Sprite(WindowPtr window, std::string texturePath) : ASprite(std::move(texturePath)),
                                                            _window(std::move(window)) {
            _sprite = sf::Sprite(getTexture(_texturePath));
        };

        void draw() override {
            applyTransform();
            _window->draw(_sprite);
        }

        RectFloat getGlobalBounds() override {
            applyTransform();
            const sf::FloatRect bounds = _sprite.getGlobalBounds();

            return (RectFloat) {
                    .left = bounds.left,
                    .top = bounds.top,
                    .width = bounds.width,
                    .height = bounds.height,
            };
        }

    private:
        void applyTransform() {
            if (_rectangle.width != -1.0F && _rectangle.height != -1.0F)
                _sprite.setTextureRect(sf::IntRect(_rectangle.left, _rectangle.top, _rectangle.width, _rectangle.height));
            _sprite.setPosition(_position.first, _position.second);
            _sprite.setScale(sf::Vector2f(_scale.first, _scale.second));
            _sprite.setOrigin(sf::Vector2f(_origin.first, _origin.second));
            _sprite.setRotation(_rotation);
            _sprite.setColor(sf::Color(_color.r, _color.g, _color.b, _color.a));
        }
    };

}
