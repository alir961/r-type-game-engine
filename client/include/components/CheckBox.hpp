/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** CheckBox.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <functional>
#include "Ui.hpp"
#include "engine/modules/logger/ILoggerModule.hpp"

namespace RType {

    /**
     * @brief On/off switch with a title and a description, clickable on the whole row.
     */
    class CheckBox {
    public:
        using ModuleCallback = std::function<void(std::string)>;

        static constexpr float WIDTH = 820.0F;
        static constexpr float HEIGHT = 96.0F;

        /**
         * @param x Left of the row
         * @param y Top of the row
         * @param boxName Name given to the callbacks (also the title)
         * @param description Short explanation under the title
         * @param active Initial state
         */
        CheckBox(float x, float y, const std::string &boxName, const std::string &description, bool active = false)
                : _x(x), _y(y), _boxName(boxName), _active(active),
                  _title(boxName, 32, Theme::Text, x + 24.0F, y + 16.0F),
                  _description(description, 22, Theme::TextDim, x + 24.0F, y + 58.0F),
                  _state("", 22, Theme::TextDim, x + WIDTH - 140.0F, y + HEIGHT / 2.0F, Align::RIGHT) {
            _row->setPosition(Vector2f(x, y));
            _row->setSize(Vector2f(WIDTH, HEIGHT));
            _row->setOutlineThickness(2.0F);
            _track->setPosition(Vector2f(x + WIDTH - 118.0F, y + (HEIGHT - 40.0F) / 2.0F));
            _track->setSize(Vector2f(92.0F, 40.0F));
            _track->setOutlineThickness(2.0F);
            _knob->setSize(Vector2f(32.0F, 32.0F));
            _knob->setBackgroundColor(Theme::Text);
            _state.setCenterY(true);
        }

        void draw() {
            const bool hovered = isHovered();
            const float knobX = _x + WIDTH - 118.0F + (_active ? 56.0F : 4.0F);

            _row->setBackgroundColor(hovered ? Color::RGB{28, 40, 82, 235} : Color::RGB{18, 24, 54, 220});
            _row->setOutlineColor(hovered ? Theme::Accent : Theme::PanelBorder);
            _track->setBackgroundColor(_active ? Theme::AccentDark : Color::RGB{40, 44, 66, 255});
            _track->setOutlineColor(_active ? Theme::Accent : Theme::PanelBorder);
            _knob->setPosition(Vector2f(knobX, _y + (HEIGHT - 32.0F) / 2.0F));
            _knob->setBackgroundColor(_active ? Theme::Accent : Theme::TextDim);
            _state.setText(_active ? "ON" : "OFF");
            _state.setColor(_active ? Theme::Accent : Theme::TextDim);
            _row->draw();
            _track->draw();
            _knob->draw();
            _title.draw();
            _description.draw();
            _state.draw();
        }

        /**
         * @brief Toggle on click and call the matching callback with the lowercase box name.
         */
        void handleInput(const ModuleCallback &loadCallback, const ModuleCallback &unloadCallback) {
            if (!_module->isMouseClicked() || !isHovered())
                return;
            std::string name = _boxName;

            std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
            _active = !_active;
            if (_active) {
                loadCallback(name);
                _logger->debug(name + " box set active");
            } else {
                unloadCallback(name);
                _logger->debug(name + " box set inactive");
            }
        }

    private:
        float _x;
        float _y;
        std::string _boxName;
        bool _active;
        Label _title;
        Label _description;
        Label _state;
        ModuleProviderPtr provider = ModuleProvider::getInstance();
        IGraphicalModule *_module = provider->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        ILoggerModule *_logger = provider->get<ILoggerModule>(ModuleType::LOGGER);
        RectShape _row = _module->createRectShape();
        RectShape _track = _module->createRectShape();
        RectShape _knob = _module->createRectShape();

        [[nodiscard]] bool isHovered() const {
            const auto &[x, y] = _module->getMousePosition();

            return x >= _x && x <= _x + WIDTH && y >= _y && y <= _y + HEIGHT;
        }
    };
}
