/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Button.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <utility>
#include <vector>
#include "Ui.hpp"
#include "Effects.hpp"

namespace RType {

    /**
     * @brief Clickable button: highlighted on hover or keyboard focus, runs its action on click.
     */
    class Button {
    private:
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        RectShape _rectangle = _module->createRectShape();
        RectShape _marker = _module->createRectShape();
        Label _label;
        std::function<void()> _action;
        float _x;
        float _y;
        float _width;
        float _height;
        bool _focused = false;
        bool _hoverHighlight = true; /**< Highlight on hover by itself (a ButtonList manages it instead). */

    public:
        Button(float x, float y, float width, float height, const std::string &text, std::function<void()> action = {})
                : _label(text, 30, Theme::Text, x + width / 2.0F, y + height / 2.0F, Align::CENTER),
                  _action(std::move(action)), _x(x), _y(y), _width(width), _height(height) {
            _rectangle->setPosition(Vector2f(x, y));
            _rectangle->setSize(Vector2f(width, height));
            _rectangle->setOutlineThickness(2.0F);
            _marker->setPosition(Vector2f(x, y));
            _marker->setSize(Vector2f(6.0F, height));
            _marker->setBackgroundColor(Theme::Accent);
            _label.setCenterY(true);
        }

        [[nodiscard]] bool isHovered() const {
            const Vector2f mouse = _module->getMousePosition();

            return mouse.first >= _x && mouse.first <= _x + _width && mouse.second >= _y && mouse.second <= _y + _height;
        }

        [[nodiscard]] bool isClicked() const {
            return isHovered() && _module->isMouseClicked();
        }

        void setFocused(bool focused) { _focused = focused; }

        void setHoverHighlight(bool hoverHighlight) { _hoverHighlight = hoverHighlight; }

        void setText(const std::string &text) { _label.setText(text); }

        void activate() const {
            Audio::play("ui_select", 60.0F);
            if (_action)
                _action();
        }

        void executeIfClicked(const std::function<void()> &function) const {
            if (isClicked()) {
                Audio::play("ui_select", 60.0F);
                function();
            }
        }

        void draw() {
            const bool highlighted = _focused || (_hoverHighlight && isHovered());

            _rectangle->setBackgroundColor(highlighted ? Color::RGB{36, 74, 124, 240} : Color::RGB{20, 26, 58, 220});
            _rectangle->setOutlineColor(highlighted ? Theme::Accent : Theme::PanelBorder);
            _label.setColor(highlighted ? Theme::Accent : Theme::Text);
            _rectangle->draw();
            if (highlighted)
                _marker->draw();
            _label.draw();
        }
    };

    /**
     * @brief Vertical stack of buttons usable with the mouse or with ↑/↓ + Enter.
     *
     * The highlighted button follows the mouse only when it moves, so a pointer resting
     * on a button doesn't fight with keyboard navigation.
     */
    class ButtonList {
    private:
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        std::vector<Button> _buttons;
        int _focus = -1; /**< Highlighted button, -1 for none. */
        Vector2f _lastMouse = _module->getMousePosition();

    public:
        static constexpr float WIDTH = 460.0F;
        static constexpr float HEIGHT = 72.0F;
        static constexpr float GAP = 20.0F;

        /**
         * @param centerX Horizontal center of the buttons
         * @param top Y of the first button
         * @param entries Text and action of each button, from top to bottom
         */
        ButtonList(float centerX, float top, const std::vector<std::pair<std::string, std::function<void()>>> &entries) {
            float y = top;

            _buttons.reserve(entries.size());
            for (const auto &[text, action]: entries) {
                _buttons.emplace_back(centerX - WIDTH / 2.0F, y, WIDTH, HEIGHT, text, action);
                _buttons.back().setHoverHighlight(false);
                y += HEIGHT + GAP;
            }
        }

        void handleEvent(const sf::Event &event) {
            if (event.type != sf::Event::KeyPressed || _buttons.empty())
                return;
            const int count = static_cast<int>(_buttons.size());

            switch (event.key.code) {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                case sf::Keyboard::Z:
                    _focus = _focus < 0 ? count - 1 : (_focus + count - 1) % count;
                    Audio::play("ui_move", 40.0F);
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                case sf::Keyboard::Tab:
                    _focus = (_focus + 1) % count;
                    Audio::play("ui_move", 40.0F);
                    break;
                case sf::Keyboard::Enter:
                case sf::Keyboard::Space:
                    _buttons[std::max(0, _focus)].activate();
                    break;
                default:
                    break;
            }
        }

        /**
         * @brief Follow the mouse and run the clicked button. Call once per frame.
         */
        void update() {
            const Vector2f mouse = _module->getMousePosition();

            if (mouse != _lastMouse) {
                const int previous = _focus;

                _lastMouse = mouse;
                _focus = -1;
                for (size_t i = 0; i < _buttons.size(); i++)
                    if (_buttons[i].isHovered())
                        _focus = static_cast<int>(i);
                if (_focus >= 0 && _focus != previous)
                    Audio::play("ui_move", 40.0F);
            }
            for (auto &button: _buttons) {
                if (button.isClicked()) {
                    button.activate();
                    return;
                }
            }
        }

        void draw() {
            for (size_t i = 0; i < _buttons.size(); i++) {
                _buttons[i].setFocused(static_cast<int>(i) == _focus);
                _buttons[i].draw();
            }
        }
    };

}
