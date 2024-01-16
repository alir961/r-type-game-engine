/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

namespace RType {

    using Vector2f = std::pair<float, float>;

    class AText {
    protected:
        std::string _text = "";
        Vector2f _position = Vector2f (0.0F, 0.0F);
        unsigned _size = 10;
        std::string _fontPath = "";

    public:
        AText() = default;

        AText(std::string text) : _text(text) {};

        void setText(const std::string &text) {
            _text = text;
        }

        void setSize(unsigned size) {
            _size = size;
        }

        void setPosition(const Vector2f &position) {
            _position = position;
        }

        void setFontPath(const std::string &fontPath) {
            _fontPath = fontPath;
        }

        virtual void draw() = 0;
    };

    using TextComponent = std::shared_ptr<AText>;

}
