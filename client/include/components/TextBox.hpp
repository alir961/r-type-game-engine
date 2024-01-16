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
     * @class TextBox
     * @brief Represents a graphical text box for displaying and interacting with text.
     */
    class TextBox {
    private:
        RectFloat _inputBoxBounds; /**< The bounding box of the text box. */
        bool _active = false; /**< Flag indicating whether the text box is currently active. */
        bool _hover = false; /**< Flag indicating whether the mouse cursor is hovering over the text box. */
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        TextComponent _text = _module->createText("");

        /**
         * @brief Updates the text content of the text box.
         */
        void updateText() {
            //_value.setString(_value.getString());
            //_inputBoxBounds = _text->getGlobalBounds();
        }

    public:
        /**
         * @brief Constructor for TextBox.
         * @param textColor The color of the text.
         * @param fontSize The size of the text.
         * @param x The x-coordinate of the text box.
         * @param y The y-coordinate of the text box.
         */
        TextBox(const Color::RGB &textColor, unsigned int fontSize, float x, float y)
                : _active(false), _hover(false) {
            _text->setSize(fontSize);
            _text->setPosition(Vector2f(x, y));
            _text->setFontPath("client/assets/ka1.ttf");
            _text->setColor(textColor);
            //updateText();
        }

        /**
         * @brief Constructor for TextBox.
         * @param textColor The color of the text.
         * @param fontSize The size of the text.
         * @param x The x-coordinate of the text box.
         * @param y The y-coordinate of the text box.
         * @param initialText The initial text to display in the text box.
         */
        TextBox(const Color::RGB &textColor, unsigned int fontSize, float x, float y, const std::string &initialText) {
            _text->setText(initialText);
            _text->setSize(fontSize);
            _text->setPosition(Vector2f(x, y));
            _text->setFontPath("client/assets/ka1.ttf");
            _text->setColor(textColor);
            //updateText();
        }

        /**
         * @brief Handles user input to determine if the text box is active or hovered.
         */
        void handleInput() {
            const Vector2f mousePosition = _module->getMousePosition();

            if (_module->isMouseClicked())
                _active = _inputBoxBounds.contains(mousePosition);
            _hover = _inputBoxBounds.contains(mousePosition);
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
            //updateText();
        }

        /**
         * @brief Gets the current activity state of the text box.
         * @return True if the text box is active, false otherwise.
         */
        bool isActive() const {
            return _active;
        }

        /**
         * @brief Change the text.
         * @param newText The new text.
         */
        void setText(std::string newText) {
            _text->setText(newText);
        }
    };

}
