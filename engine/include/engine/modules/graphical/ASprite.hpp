/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <utility>

#include "DataCommon.hpp"

namespace RType {

    class ASprite {
    protected:
        std::string _texturePath = "";
        Vector2f _position = Vector2f(0.0F, 0.0F);
        Vector2f _scale = Vector2f(1.0F, 1.0F);
        Vector2f _origin = Vector2f(0.0F, 0.0F);
        RectFloat _rectangle = RectFloat{0.0F, 0.0F, -1.0F, -1.0F};
        float _rotation = 0.0F;
        Color::RGB _color = Color::White;

    public:
        explicit ASprite(std::string texturePath) : _texturePath(std::move(texturePath)) {};

        virtual ~ASprite() = default;

        void move(float x, float y) {
            _position.first += x;
            _position.second += y;
        }

        const Vector2f &getPosition() const {
            return _position;
        }

        void setPosition(const Vector2f &position) {
            _position = position;
        }

        void setScale(const Vector2f &scale) {
            _scale = scale;
        }

        void setOrigin(const Vector2f &origin) {
            _origin = origin;
        }

        void setRotation(float rotation) {
            _rotation = rotation;
        }

        void setRectangle(const RectFloat &rectangle) {
            _rectangle = rectangle;
        }

        /**
         * @brief Multiply the texture by a color (white keeps it unchanged).
         */
        void setColor(const Color::RGB &color) {
            _color = color;
        }

        virtual void draw() = 0;

        virtual RectFloat getGlobalBounds() = 0;
    };

    using SpriteComponent = std::shared_ptr<ASprite>;

}