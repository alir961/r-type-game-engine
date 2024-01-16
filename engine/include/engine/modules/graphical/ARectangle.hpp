/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <memory>
#include <iostream>
#include "DataCommon.hpp"

namespace RType {

    class ARectangle {
    protected:
        Vector2f _size = Vector2f(0.0F, 0.0F);
        Vector2f _position = Vector2f(0.0F, 0.0F);
        Color::RGB _backgroundColor = Color::Red;
        Color::RGB _outlineColor = Color::Transparent;
        float _outlineThickness = 0.0F;

    public:
        ARectangle() {
            std::cout << "Init rectangle\n";
        };

        virtual ~ARectangle() {
            std::cout << "Destroy rectangle\n";
        };

        void setSize(const Vector2f &size) {
            _size = Vector2f(size.first, size.second);
        }

        void setPosition(const Vector2f &position) {
            _position = Vector2f(position.first, position.second);
        }

        void setBackgroundColor(const Color::RGB &backgroundColor) {
            _backgroundColor = Color::RGB{backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a};
        }

        void setOutlineColor(const Color::RGB &outlineColor) {
            _outlineColor = Color::RGB{outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a};
        }

        void setOutlineThickness(float outlineThickness) {
            _outlineThickness = outlineThickness;
        }

        virtual RectFloat getGlobalBounds() = 0;

        virtual void draw() = 0;
    };

    using RectShape = std::shared_ptr<ARectangle>;

}
