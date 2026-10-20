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

    class AText {
    protected:
        std::string _value = "";
        Vector2f _position = Vector2f(0.0F, 0.0F);
        unsigned _size = 10;
        Color::RGB _color = Color::White;
        std::string _fontPath = "";
        float _outlineThickness = 0.0F;
        Color::RGB _outlineColor = Color::Black;

    public:
        AText() = default;

        explicit AText(std::string text) : _value(std::move(text)) {};

        virtual ~AText() = default;

        void setText(const std::string_view &text) {
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

        void setFontPath(const std::string_view &fontPath) {
            _fontPath = fontPath;
        }

        void setOutline(float thickness, const Color::RGB &color = Color::Black) {
            _outlineThickness = thickness;
            _outlineColor = color;
        }

        [[nodiscard]] const Vector2f &getPosition() const {
            return _position;
        }

        virtual void draw() = 0;

        virtual RectFloat getGlobalBounds() = 0;
    };

    using TextComponent = std::shared_ptr<AText>;

}
