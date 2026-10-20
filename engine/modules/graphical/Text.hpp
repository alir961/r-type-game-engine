/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <unordered_map>
#include <utility>

#include "engine/modules/graphical/AText.hpp"

namespace RType {

    constexpr const char *DEFAULT_FONT_PATH = "client/assets/ka1.ttf";

    class Text : public AText {
    private:
        WindowPtr _window;

        /**
         * @brief Load each font file once and share it between every text.
         */
        static const sf::Font &getFont(const std::string &path) {
            static std::unordered_map<std::string, sf::Font> fonts;
            const std::string &fontPath = path.empty() ? DEFAULT_FONT_PATH : path;
            auto iterator = fonts.find(fontPath);

            if (iterator == fonts.end()) {
                iterator = fonts.try_emplace(fontPath).first;
                iterator->second.loadFromFile(fontPath);
            }
            return iterator->second;
        }

        [[nodiscard]] sf::Text buildText() const {
            sf::Text text(sf::String::fromUtf8(_value.begin(), _value.end()), getFont(_fontPath), _size);

            text.setPosition(sf::Vector2f(_position.first, _position.second));
            text.setFillColor(sf::Color(_color.r, _color.g, _color.b, _color.a));
            text.setOutlineThickness(_outlineThickness);
            text.setOutlineColor(sf::Color(_outlineColor.r, _outlineColor.g, _outlineColor.b, _outlineColor.a));
            return text;
        }

    public:
        explicit Text(WindowPtr window) : _window(std::move(window)) {};

        Text(WindowPtr window, const std::string &text) : AText(text), _window(std::move(window)) {};

        void draw() override {
            _window->draw(buildText());
        }

        RectFloat getGlobalBounds() override {
            const sf::FloatRect bounds = buildText().getGlobalBounds();

            return RectFloat{
                    .left = bounds.left,
                    .top = bounds.top,
                    .width = bounds.width,
                    .height = bounds.height,
            };
        }
    };

}
