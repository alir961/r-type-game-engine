/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Ui.hpp
*/

#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include "engine/modules/graphical/IGraphicalModule.hpp"
#include "engine/modules/ModuleProvider.hpp"

namespace RType {

    /**
     * @brief Shared palette and fonts so every screen looks like the same game.
     */
    namespace Theme {
        static const Color::RGB Background{6, 8, 22, 255};
        static const Color::RGB Dim{4, 6, 16, 170};
        static const Color::RGB Panel{14, 18, 44, 225};
        static const Color::RGB PanelBorder{62, 86, 160, 255};
        static const Color::RGB Accent{84, 220, 255, 255};
        static const Color::RGB AccentDark{24, 70, 104, 255};
        static const Color::RGB Text{232, 238, 255, 255};
        static const Color::RGB TextDim{146, 158, 196, 255};
        static const Color::RGB Success{110, 232, 140, 255};
        static const Color::RGB Warning{255, 192, 70, 255};
        static const Color::RGB Danger{255, 92, 92, 255};
        static const Color::RGB Shadow{0, 0, 0, 200};
        static const Color::RGB KeyFill{30, 38, 78, 255};
        static const Color::RGB KeyBorder{126, 152, 232, 255};

        constexpr const char *FONT = "client/assets/Basic-Regular.ttf";
        constexpr float CENTER_X = static_cast<float>(WINDOW_WIDTH) / 2.0F;
        constexpr float CENTER_Y = static_cast<float>(WINDOW_HEIGHT) / 2.0F;

        /**
         * @brief Map a player color name sent by the server ("purplePlayer" or "purple") to its RGB.
         */
        inline Color::RGB playerColor(const std::string &name) {
            if (name.starts_with("purple")) return {176, 104, 244, 255};
            if (name.starts_with("green")) return {104, 226, 104, 255};
            if (name.starts_with("red")) return {244, 90, 98, 255};
            if (name.starts_with("blue")) return {92, 146, 252, 255};
            return {56, 216, 206, 255};
        }

        /**
         * @brief Green when healthy, orange when hurt, red when critical.
         */
        inline Color::RGB healthColor(float ratio) {
            if (ratio > 0.6F) return Success;
            if (ratio > 0.3F) return Warning;
            return Danger;
        }
    }

    enum class Align {
        LEFT,
        CENTER,
        RIGHT,
    };

    /**
     * @brief A piece of text anchored on a point, with a shadow outline to stay readable over the starfield.
     */
    class Label {
    private:
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        TextComponent _text = _module->createText("");
        float _x;
        float _y;
        Align _align;
        bool _centerY = false;

        void place() {
            _text->setPosition(Vector2f(_x, _y));
            if (_align == Align::LEFT && !_centerY)
                return;
            const RectFloat bounds = _text->getGlobalBounds();
            float x = _x;
            float y = _y;

            if (_align == Align::CENTER)
                x += _x - (bounds.left + bounds.width / 2.0F);
            else if (_align == Align::RIGHT)
                x += _x - (bounds.left + bounds.width);
            if (_centerY)
                y += _y - (bounds.top + bounds.height / 2.0F);
            _text->setPosition(Vector2f(x, y));
        }

    public:
        Label(const std::string &text, unsigned int size, const Color::RGB &color, float x, float y,
              Align align = Align::LEFT) : _x(x), _y(y), _align(align) {
            _text->setText(text);
            _text->setSize(size);
            _text->setColor(color);
            _text->setFontPath(Theme::FONT);
            _text->setOutline(size >= 40 ? 3.0F : 1.5F, Theme::Shadow);
        }

        void setText(const std::string &text) { _text->setText(text); }

        void setColor(const Color::RGB &color) { _text->setColor(color); }

        void setPosition(float x, float y) {
            _x = x;
            _y = y;
        }

        /**
         * @brief Treat the position as the vertical center of the text instead of its top.
         */
        void setCenterY(bool centerY) { _centerY = centerY; }

        float getWidth() {
            place();
            return _text->getGlobalBounds().width;
        }

        void draw() {
            place();
            _text->draw();
        }
    };

    /**
     * @brief Filled rectangle with a border, used behind every block of UI.
     */
    class Panel {
    private:
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        RectShape _body = _module->createRectShape();
        RectShape _accent = _module->createRectShape();

    public:
        Panel(float x, float y, float width, float height, const Color::RGB &fill = Theme::Panel) {
            _body->setPosition(Vector2f(x, y));
            _body->setSize(Vector2f(width, height));
            _body->setBackgroundColor(fill);
            _body->setOutlineColor(Theme::PanelBorder);
            _body->setOutlineThickness(2.0F);
            _accent->setPosition(Vector2f(x, y));
            _accent->setSize(Vector2f(width, 4.0F));
            _accent->setBackgroundColor(Theme::Accent);
        }

        void draw() {
            _body->draw();
            _accent->draw();
        }
    };

    /**
     * @brief Draws keyboard keys ("SPACE", "ESC"...) for the control guides.
     */
    class KeyCap {
    public:
        static constexpr float HEIGHT = 52.0F;

        /**
         * @brief Draw one key with its top-left corner at (x, y).
         * @return The key width, so callers can lay keys out in a row
         */
        static float draw(const std::string &key, float x, float y) {
            IGraphicalModule *module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
            // Count characters, not UTF-8 bytes, so "←" is as wide as "A".
            const auto characters = std::count_if(key.begin(), key.end(), [](char c) { return (c & 0xC0) != 0x80; });
            const float width = std::max(HEIGHT, 26.0F + 17.0F * static_cast<float>(characters));
            RectShape shadow = module->createRectShape();
            RectShape cap = module->createRectShape();
            Label label(key, 24, Theme::Text, x + width / 2.0F, y + HEIGHT / 2.0F - 3.0F, Align::CENTER);

            shadow->setPosition(Vector2f(x, y + 6.0F));
            shadow->setSize(Vector2f(width, HEIGHT));
            shadow->setBackgroundColor(Theme::AccentDark);
            cap->setPosition(Vector2f(x, y));
            cap->setSize(Vector2f(width, HEIGHT));
            cap->setBackgroundColor(Theme::KeyFill);
            cap->setOutlineColor(Theme::KeyBorder);
            cap->setOutlineThickness(2.0F);
            label.setCenterY(true);
            shadow->draw();
            cap->draw();
            label.draw();
            return width;
        }

        /**
         * @brief Draw several keys separated by a small gap.
         * @return The total width of the row
         */
        static float drawRow(const std::vector<std::string> &keys, float x, float y, float gap = 10.0F) {
            float cursor = x;

            for (const auto &key: keys)
                cursor += draw(key, cursor, y) + gap;
            return cursor - x - gap;
        }
    };

}
