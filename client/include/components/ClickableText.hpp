/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** IGraphicEntity.hpp
*/

#pragma once

#include "engine/modules/graphical/AText.hpp"

namespace RType {

    /**
     * @class ClickableText
     * @brief Represents a graphical text box for displaying and interacting with text.
     */
    class ClickableText {
    private:
        RectFloat _inputBoxBounds; /**< The bounding box of the text box. */
        bool _clicked = false; /**< Flag indicating whether the text box is currently active. */
        bool _hover = false; /**< Flag indicating whether the mouse cursor is hovering over the text box. */
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        TextComponent _text = _module->createText("");

    public:
        /**
         * @brief Constructor for ClickableText.
         * @param textColor The color of the text.
         * @param fontSize The size of the text.
         * @param x The x-coordinate of the text box.
         * @param y The y-coordinate of the text box.
         */
        ClickableText(const Color::RGB &textColor, unsigned int fontSize, float x, float y) {
            _text->setSize(fontSize);
            _text->setPosition(Vector2f(x, y));
            _text->setFontPath("client/assets/ka1.ttf");
            _text->setColor(textColor);
        }

        /**
         * @brief Constructor for ClickableText.
         * @param textColor The color of the text.
         * @param fontSize The size of the text.
         * @param x The x-coordinate of the text box.
         * @param y The y-coordinate of the text box.
         * @param initialText The initial text to display in the text box.
         */
        ClickableText(const Color::RGB &textColor, unsigned int fontSize, float x, float y, const std::string &initialText) {
            _text->setText(initialText);
            _text->setSize(fontSize);
            _text->setPosition(Vector2f(x, y));
            _text->setFontPath("client/assets/ka1.ttf");
            _text->setColor(textColor);
        }

        /**
         * @brief Handles user input to determine if the text box is active or hovered.
         */
        void handleInput() {
            const Vector2f mousePosition = _module->getMousePosition();

            _hover = _text->getGlobalBounds().contains(mousePosition);
            if (_module->isMouseClicked())
                _clicked = _hover;
        }

        /**
         * @brief Updates the appearance of the text box based on its state.
         */
        void update() {
            if (_hover)
                _text->setColor(Color::Cyan);
            else _text->setColor(Color::Magenta);
        }

        /**
         * @brief Draws the text box on the associated SFML RenderWindow.
         */
        void draw() {
            _text->draw();
        }

        /**
         * @brief Gets the current activity state of the text box.
         * @return True if the text box is active, false otherwise.
         */
        [[nodiscard]] bool isClicked() const {
            return _clicked;
        }

        /**
         * @brief Change the text.
         * @param value The new text.
         */
        void setText(const std::string & value) {
            _text->setText(value);
        }
    };

}
