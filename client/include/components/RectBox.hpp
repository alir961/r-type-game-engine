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
            : _window(window), _position(position), _size(size), _fillColor(fillColor),
              _outlineColor(outlineColor), _outlineThickness(outlineThickness) {
            _rectangle.setPosition(position);
            _rectangle.setSize(size);
            _rectangle.setFillColor(fillColor);
            _rectangle.setOutlineColor(outlineColor);
            _rectangle.setOutlineThickness(outlineThickness);
        }

        /**
         * @brief Draws the rectangle on the associated SFML RenderWindow.
         */
        void draw(IGraphicalModule *graphicalModule) {
            graphicalModule->drawRect(_rectangle);
        }

        /**
         * @brief Sets the position of the rectangle.
         * @param newPosition The new position of the top-left corner of the rectangle.
         */
        void setPosition(const sf::Vector2f &newPosition) {
            _position = newPosition;
            _rectangle.setPosition(_position);
        }

        /**
         * @brief Sets the size of the rectangle.
         * @param newSize The new size of the rectangle.
         */
        void setSize(const sf::Vector2f &newSize) {
            _size = newSize;
            _rectangle.setSize(_size);
        }

        /**
         * @brief Sets the color to fill the rectangle.
         * @param newFillColor The new fill color of the rectangle.
         */
        void setFillColor(const sf::Color &newFillColor) {
            _fillColor = newFillColor;
            _rectangle.setFillColor(_fillColor);
        }

        /**
         * @brief Sets the color of the outline of the rectangle.
         * @param newOutlineColor The new outline color of the rectangle.
         */
        void setOutlineColor(const sf::Color &newOutlineColor) {
            _outlineColor = newOutlineColor;
            _rectangle.setOutlineColor(_outlineColor);
        }

        /**
         * @brief Sets the thickness of the outline of the rectangle.
         * @param newOutlineThickness The new outline thickness of the rectangle.
         */
        void setOutlineThickness(float newOutlineThickness) {
            _outlineThickness = newOutlineThickness;
            _rectangle.setOutlineThickness(_outlineThickness);
        }

    private:
        sf::RenderWindow &_window; /**< The SFML RenderWindow where the rectangle box will be drawn. */
        sf::Vector2f _position; /**< The position of the top-left corner of the rectangle. */
        sf::Vector2f _size; /**< The size of the rectangle. */
        sf::Color _fillColor; /**< The color to fill the rectangle. */
        sf::Color _outlineColor; /**< The color of the outline of the rectangle. */
        float _outlineThickness; /**< The thickness of the outline of the rectangle. */
        sf::RectangleShape _rectangle; /**< The SFML RectangleShape representing the rectangle box. */
    };
}
