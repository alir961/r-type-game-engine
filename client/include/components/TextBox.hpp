/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** IGraphicEntity.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>

namespace RType {
    /**
     * @class TextBox
     * @brief Represents a graphical text box for displaying and interacting with text.
     */
    class TextBox {
    public:
        /**
         * @brief Constructor for TextBox.
         * @param window The SFML RenderWindow where the text box will be drawn.
         * @param textColor The color of the text.
         * @param fontSize The size of the text.
         * @param x The x-coordinate of the text box.
         * @param y The y-coordinate of the text box.
         * @param initialText The initial text to display in the text box.
         */
        TextBox(sf::RenderWindow &window, const sf::Color &textColor, unsigned int fontSize, float x, float y, const std::string &initialText = "")
            : _window(window), _textColor(textColor), _fontSize(fontSize), _isActive(false), _isHovered(false) {
            _font.loadFromFile("client/assets/ka1.ttf");
            _text.setFont(_font);
            _text.setCharacterSize(fontSize);
            _text.setPosition(x, y);
            _text.setString(initialText);
            _text.setFillColor(textColor);
            updateText();
        }

        /**
         * @brief Handles user input to determine if the text box is active or hovered.
         */
        void handleInput() {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(_window));
                if (_inputBoxBounds.contains(mousePosition)) {
                    setActive(true);
                } else {
                    setActive(false);
                }
            }
            sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(_window));
            _isHovered = _inputBoxBounds.contains(mousePosition);
        }

        /**
         * @brief Updates the appearance of the text box based on its state.
         */
        void update() {
            if (_isHovered) {
                _text.setFillColor(sf::Color::Cyan);
            } else {
                _text.setFillColor(sf::Color::Magenta);
            }
        }

        /**
         * @brief Draws the text box on the associated SFML RenderWindow.
         */
        void draw(IGraphicalModule *graphicalModule) {
            graphicalModule->drawText(_window, _text);
        }

        /**
         * @brief Sets the activity state of the text box.
         * @param active True to set the text box as active, false otherwise.
         */
        void setActive(bool active) {
            _isActive = active;
        }

        /**
         * @brief Gets the current activity state of the text box.
         * @return True if the text box is active, false otherwise.
         */
        bool getActive() const {
            return _isActive;
        }

        /**
         * @brief Gets the font used for rendering text in the text box.
         * @return The SFML Font object.
         */
        const sf::Font &getFont() const {
            return _font;
        }

        /**
         * @brief Change the font size of the text.
         * @param newSize The new font size.
         */
        void setFontSize(unsigned int newSize) {
            _fontSize = newSize;
            _text.setCharacterSize(_fontSize);
            updateText();
        }

        /**
         * @brief Change the text.
         * @param newText The new text.
         */
        void setText(std::string newText) {
            _text.setString(newText);
        }

    private:
        sf::RenderWindow& _window; /**< The SFML RenderWindow where the text box will be drawn. */
        sf::Color _textColor; /**< The color of the text. */
        sf::Text _text; /**< The SFML Text object representing the text box content. */
        sf::Font _font; /**< The SFML Font used for rendering text. */
        sf::FloatRect _inputBoxBounds; /**< The bounding box of the text box. */
        bool _isActive; /**< Flag indicating whether the text box is currently active. */
        bool _isHovered; /**< Flag indicating whether the mouse cursor is hovering over the text box. */
        unsigned int _fontSize; /**< The size of the text. */

        /**
         * @brief Updates the text content of the text box.
         */
        void updateText() {
            _text.setString(_text.getString());
            _inputBoxBounds = _text.getGlobalBounds();
        }
    };
}
