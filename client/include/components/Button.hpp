/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

namespace RType {

    /**
     * @class Button
     * @brief Represents a simple clickable button using SFML.
     * @tparam width The width of the button.
     * @tparam height The height of the button.
     */
    template<int width, int height>
    class Button {
    private:
        int _x; /**< X-coordinate of the button. */
        int _y; /**< Y-coordinate of the button. */
        std::string _value; /**< Text displayed on the button. */
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        TextComponent _text = _module->createText("");
        RectShape _rectangle = _module->createRectShape();

    public:
        /**
         * @brief Constructor for the Button class.
         * @param x The X-coordinate of the button.
         * @param y The Y-coordinate of the button.
         * @param text The text to be displayed on the button.
         */
        Button(float x, float y, std::string text) : _x(x), _y(y), _value(std::move(text)) {
            _rectangle->setPosition(Vector2f(x, y));
            _rectangle->setSize(Vector2f(static_cast<float>(width), static_cast<float>(height)));

            _text->setSize(20);
            _text->setText(_value);
            _text->setFontPath("client/assets/ka1.ttf");
            _text->setPosition(Vector2f(_x + 20, _y + 10));
        }

        /**
         * @brief Draws the button on the SFML RenderWindow.
         */
        void draw() {
            const auto &[x, y] = _module->getMousePosition();
            bool mouseOver = _rectangle->getGlobalBounds().contains(Vector2f(x, y));

            _rectangle->setBackgroundColor(mouseOver ? Color::RGB{200, 200, 200, 255} : Color::RGB{128, 128, 128, 255});
            _rectangle->draw();
            _text->draw();
        }

        ~Button() = default;

        /**
         * @brief Executes a function if the button is clicked.
         * @param function The function to execute.
         */
        void executeIfClicked(const std::function<void()> &function) {
            const auto &[x, y] = _module->getMousePosition();
            bool mouseOver = _rectangle->getGlobalBounds().contains(Vector2f(x, y));
            bool mouseClick = _module->isMouseClicked();

            if (mouseOver && mouseClick)
                function();
        }
    };

}
