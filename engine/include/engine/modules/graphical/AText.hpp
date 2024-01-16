/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "DataCommon.hpp"

namespace RType {

    class AText {
    protected:
        std::string _value = "";
        Vector2f _position = Vector2f(0.0F, 0.0F);
        unsigned _size = 10;
        Color::RGB _color = Color::White;
        std::string _fontPath = "";

    public:
        AText() = default;

        AText(std::string text) : _value(text) {};

        void setText(const std::string &text) {
            _value = text;
        }

        void setSize(unsigned size) {
            _size = size;
        }

        void setPosition(const Vector2f &position) {
            _position = position;
        }

        void setColor(const Color::RGB &color) {
            _color = color;
        }

        void setFontPath(const std::string &fontPath) {
            _fontPath = fontPath;
        }

        virtual void draw() = 0;

        //virtual RectFloat getGlobalBounds() = 0;
    };

    using TextComponent = std::shared_ptr<AText>;

}
