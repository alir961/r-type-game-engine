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
         * @param x The x-coordinate of the text box.
         * @param y The y-coordinate of the text box.
         * @param initialText The initial text to display in the text box.
         */
        TextBox(sf::RenderWindow &window, const sf::Color &textColor, float x, float y, const std::string &initialText = "")
            : _window(window), textColor(textColor), isActive(false), isHovered(false) {
            font.loadFromFile("client/assets/ka1.ttf");
            text.setFont(font);
            text.setCharacterSize(20);
            text.setPosition(x, y);
            text.setString(initialText);
            text.setFillColor(textColor);
            updateText();
        }

        /**
         * @brief Handles user input to determine if the text box is active or hovered.
         */
        void handleInput() {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(_window));
                if (inputBoxBounds.contains(mousePosition)) {
                    setActive(true);
                } else {
                    setActive(false);
                }
            }
            sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(_window));
            isHovered = inputBoxBounds.contains(mousePosition);
        }

        /**
         * @brief Updates the appearance of the text box based on its state.
         */
        void update() {
            if (isHovered) {
                text.setFillColor(sf::Color::Cyan);
            } else {
                text.setFillColor(sf::Color::Magenta);
            }
        }

        /**
         * @brief Draws the text box on the associated SFML RenderWindow.
         */
        void draw() {
            _window.draw(text);
        }

        /**
         * @brief Sets the activity state of the text box.
         * @param active True to set the text box as active, false otherwise.
         */
        void setActive(bool active) {
            isActive = active;
        }

        /**
         * @brief Gets the current activity state of the text box.
         * @return True if the text box is active, false otherwise.
         */
        bool getActive() const {
            return isActive;
        }

        /**
         * @brief Gets the font used for rendering text in the text box.
         * @return The SFML Font object.
         */
        const sf::Font &getFont() const {
            return font;
        }

    private:
        sf::RenderWindow& _window; /**< The SFML RenderWindow where the text box will be drawn. */
        sf::Color textColor; /**< The color of the text. */
        sf::Text text; /**< The SFML Text object representing the text box content. */
        sf::Font font; /**< The SFML Font used for rendering text. */
        sf::FloatRect inputBoxBounds; /**< The bounding box of the text box. */
        bool isActive; /**< Flag indicating whether the text box is currently active. */
        bool isHovered; /**< Flag indicating whether the mouse cursor is hovering over the text box. */

        /**
         * @brief Updates the text content of the text box.
         */
        void updateText() {
            text.setString(text.getString());
            inputBoxBounds = text.getGlobalBounds();
        }
    };
}
