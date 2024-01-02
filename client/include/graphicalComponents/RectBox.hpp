/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** RectBox.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>

namespace RType {
    /**
     * @class RectBox
     * @brief Represents a graphical rectangle box.
     */
    class RectBox {
    public:
        /**
         * @brief Constructor for RectBox.
         * @param window The SFML RenderWindow where the rectangle box will be drawn.
         * @param position The position of the top-left corner of the rectangle.
         * @param size The size of the rectangle.
         * @param fillColor The color to fill the rectangle.
         * @param outlineColor The color of the outline of the rectangle.
         * @param outlineThickness The thickness of the outline of the rectangle.
         */
        RectBox(sf::RenderWindow &window, const sf::Vector2f &position, const sf::Vector2f &size,
                const sf::Color &fillColor = sf::Color::White, const sf::Color &outlineColor = sf::Color::Black,
                float outlineThickness = 0.0f)
            : _window(window), position(position), size(size), fillColor(fillColor),
              outlineColor(outlineColor), outlineThickness(outlineThickness) {
            rectangle.setPosition(position);
            rectangle.setSize(size);
            rectangle.setFillColor(fillColor);
            rectangle.setOutlineColor(outlineColor);
            rectangle.setOutlineThickness(outlineThickness);
        }

        /**
         * @brief Draws the rectangle on the associated SFML RenderWindow.
         */
        void draw(IGraphicalModule *graphicalModule) {
            graphicalModule->drawRect(_window, rectangle);
        }

        /**
         * @brief Sets the position of the rectangle.
         * @param newPosition The new position of the top-left corner of the rectangle.
         */
        void setPosition(const sf::Vector2f &newPosition) {
            position = newPosition;
            rectangle.setPosition(position);
        }

        /**
         * @brief Sets the size of the rectangle.
         * @param newSize The new size of the rectangle.
         */
        void setSize(const sf::Vector2f &newSize) {
            size = newSize;
            rectangle.setSize(size);
        }

        /**
         * @brief Sets the color to fill the rectangle.
         * @param newFillColor The new fill color of the rectangle.
         */
        void setFillColor(const sf::Color &newFillColor) {
            fillColor = newFillColor;
            rectangle.setFillColor(fillColor);
        }

        /**
         * @brief Sets the color of the outline of the rectangle.
         * @param newOutlineColor The new outline color of the rectangle.
         */
        void setOutlineColor(const sf::Color &newOutlineColor) {
            outlineColor = newOutlineColor;
            rectangle.setOutlineColor(outlineColor);
        }

        /**
         * @brief Sets the thickness of the outline of the rectangle.
         * @param newOutlineThickness The new outline thickness of the rectangle.
         */
        void setOutlineThickness(float newOutlineThickness) {
            outlineThickness = newOutlineThickness;
            rectangle.setOutlineThickness(outlineThickness);
        }

    private:
        sf::RenderWindow &_window; /**< The SFML RenderWindow where the rectangle box will be drawn. */
        sf::Vector2f position; /**< The position of the top-left corner of the rectangle. */
        sf::Vector2f size; /**< The size of the rectangle. */
        sf::Color fillColor; /**< The color to fill the rectangle. */
        sf::Color outlineColor; /**< The color of the outline of the rectangle. */
        float outlineThickness; /**< The thickness of the outline of the rectangle. */
        sf::RectangleShape rectangle; /**< The SFML RectangleShape representing the rectangle box. */
    };
}
