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
        sf::Color _textColor; /**< The color of the text. */
        sf::FloatRect _inputBoxBounds; /**< The bounding box of the text box. */
        bool _active; /**< Flag indicating whether the text box is currently active. */
        bool _hover; /**< Flag indicating whether the mouse cursor is hovering over the text box. */
        unsigned int _fontSize; /**< The size of the text. */
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        TextComponent _text = _module->createText("");

        /**
         * @brief Updates the text content of the text box.
         */
        void updateText() {
            //_value.setString(_value.getString());
            //_inputBoxBounds = _value.getGlobalBounds();
        }

    public:
        /**
         * @brief Constructor for TextBox.
         * @param textColor The color of the text.
         * @param fontSize The size of the text.
         * @param x The x-coordinate of the text box.
         * @param y The y-coordinate of the text box.
         */
        TextBox(const sf::Color &textColor, unsigned int fontSize, float x, float y)
            : _textColor(textColor), _active(false), _hover(false), _fontSize(fontSize) {
            _text->setSize(fontSize);
            _text->setPosition(Vector2f(x, y));
            _text->setFontPath("client/assets/ka1.ttf");
            //_value.setFillColor(textColor);
            updateText();
        }

        /**
         * @brief Constructor for TextBox.
         * @param textColor The color of the text.
         * @param fontSize The size of the text.
         * @param x The x-coordinate of the text box.
         * @param y The y-coordinate of the text box.
         * @param initialText The initial text to display in the text box.
         */
        TextBox(const sf::Color &textColor, unsigned int fontSize, float x, float y, const std::string &initialText)
                : _textColor(textColor), _active(false), _hover(false), _fontSize(fontSize) {
            _text->setText(initialText);
            _text->setSize(fontSize);
            _text->setPosition(Vector2f(x, y));
            _text->setFontPath("client/assets/ka1.ttf");
            //_value.setFillColor(textColor);
            updateText();
        }

        /**
         * @brief Handles user input to determine if the text box is active or hovered.
         */
        void handleInput() {
            const Vector2f mousePosition = _module->getMousePosition();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                /*if (_inputBoxBounds.contains(mousePosition)) {
                    _active = true;
                } else {
                    _active = false;
                }*/
            }
            //_hover = _inputBoxBounds.contains(mousePosition);
        }

        /**
         * @brief Updates the appearance of the text box based on its state.
         */
        void update() {
            if (_hover) {
                //_value.setFillColor(sf::Color::Cyan);
            } else {
                //_value.setFillColor(sf::Color::Magenta);
            }
        }

        /**
         * @brief Draws the text box on the associated SFML RenderWindow.
         */
        void draw() {
            _text->draw();
        }

        /**
         * @brief Sets the activity state of the text box.
         * @param active True to set the text box as active, false otherwise.
         */
        void setActive(bool active) {
            _active = active;
        }

        /**
         * @brief Gets the current activity state of the text box.
         * @return True if the text box is active, false otherwise.
         */
        bool isActive() const {
            return _active;
        }

        /**
         * @brief Change the font size of the text.
         * @param newSize The new font size.
         */
        void setFontSize(unsigned int newSize) {
            _fontSize = newSize;
            _text->setSize(_fontSize);
            updateText();
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
