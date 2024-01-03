/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include "engine/modules/IModule.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace RType {

    class IGraphicalModule : public IModule {
    public:
        virtual void load() = 0;
        virtual void unload() = 0;

        /**
         * @brief Draw a text in SFML.
         * @param window, text The window where to draw, the text we want to display.
         */
        virtual void drawText(sf::RenderWindow &window, sf::Text text) = 0;

        /**
         * @brief Draw a sprite in SFMl.
         * @param window, sprite The window where to draw, the sprite we want to display.
         */
        virtual void drawSprite(sf::RenderWindow &window, sf::Sprite sprite) = 0;

        /**
         * @brief Draw a sprite in SFMl.
         * @param window, rect The window where to draw, the rect we want to display.
         */
        virtual void drawRect(sf::RenderWindow &window, sf::RectangleShape rect) = 0;

        /**
         * @brief Draw a text like a pro in SFML.
         * @param window, text The window where to draw, the text we want to display.
         */
        virtual void drawTextPro(sf::RenderWindow &window, const std::string &colorName, unsigned int fontSize, float x, float y, const std::string &fontPath, const std::string &initialText) = 0;

        /**
         * @brief Draw a sprite like a pro in SFMl.
         * @param window, sprite The window where to draw, the sprite we want to display.
         */
        virtual void drawSpritePro(sf::RenderWindow &window, float spriteScaleX, float spriteScaleY, float x, float y, const std::string &texturePath) = 0;

        /**
         * @brief Draw a sprite like a pro in SFMl.
         * @param window, rect The window where to draw, the rect we want to display.
         */
        virtual void drawRectPro(sf::RenderWindow &window, float rectScaleX, float rectScaleY, float x, float y, const std::string &lineColor, const std::string &fillColor, const std::string &texturePath) = 0;

        /**
         * @brief Return the sf::Color corresponding to the colorName param.
         * @param colorName The color we want to get into SFML.
         */
        virtual sf::Color getColorFromString(const std::string &colorName) = 0;
    };
}
