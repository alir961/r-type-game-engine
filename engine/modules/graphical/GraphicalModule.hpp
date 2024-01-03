/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include "engine/modules/IGraphicalModule.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace RType {

    class GraphicalModule : public IGraphicalModule {
    public:
        void load() override;
        void unload() override;

        /**
         * @brief Draw a text in SFML.
         * @param window, text The window where to draw, the text we want to display.
         */
        void drawText(sf::RenderWindow &window, sf::Text text) override;

        /**
         * @brief Draw a sprite in SFMl.
         * @param window, sprite The window where to draw, the sprite we want to display.
         */
        void drawSprite(sf::RenderWindow &window, sf::Sprite sprite) override;

        /**
         * @brief Draw a sprite in SFMl.
         * @param window, rect The window where to draw, the rect we want to display.
         */
        void drawRect(sf::RenderWindow &window, sf::RectangleShape rect) override;

        /**
         * @brief Draw a text like a pro in SFML.
         * @param window, text The window where to draw, the text we want to display.
         */
        void drawTextPro(sf::RenderWindow &window, const std::string &colorName, unsigned int fontSize, float x, float y, const std::string &fontPath, const std::string &initialText) override;

        /**
         * @brief Draw a sprite like a pro in SFMl.
         * @param window, sprite The window where to draw, the sprite we want to display.
         */
        void drawSpritePro(sf::RenderWindow &window, float spriteScaleX, float spriteScaleY, float x, float y, const std::string &texturePath) override;

        /**
         * @brief Draw a sprite like a pro in SFMl.
         * @param window, rect The window where to draw, the rect we want to display.
         */
        void drawRectPro(sf::RenderWindow &window, float rectScaleX, float rectScaleY, float x, float y, float outlineThickness, const std::string &lineColor, const std::string &fillColor, const std::string &texturePath) override;

        /**
         * @brief Return the sf::Color corresponding to the colorName param.
         * @param colorName The color we want to get into SFML.
         */
        sf::Color getColorFromString(const std::string &colorName) override;
    };
}
