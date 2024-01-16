/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "engine/modules/IModule.hpp"
#include "Event.hpp"
#include "AText.hpp"
#include "ARectangle.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace RType {

    class IGraphicalModule : public IModule {
    public:
        virtual void load() = 0;
        virtual void unload() = 0;

        virtual void openWindow(uint32_t width, uint32_t height, std::string title) = 0;

        virtual void close() = 0;

        virtual bool isOpen() = 0;

        virtual void clear() = 0;

        virtual void display() = 0;

        virtual bool pollEvent(sf::Event &event) = 0;

        virtual Vector2f getMousePosition() = 0;

        virtual bool isMouseClicked() = 0;

        /**
         * @brief Draw a text in SFML.
         * @param window, text The window where to draw, the text we want to display.
         */
        virtual TextComponent createText(const std::string &text) = 0;

        virtual RectShape createRectShape() = 0;

        /**
         * @brief Draw a sprite in SFMl.
         * @param window, sprite The window where to draw, the sprite we want to display.
         */
        virtual void drawSprite(sf::Sprite sprite) = 0;

        /**
         * @brief Draw a sprite in SFMl.
         * @param window, rect The window where to draw, the rect we want to display.
         */
        virtual void drawRect(sf::RectangleShape rect) = 0;

        /**
         * @brief Draw a text like a pro in SFML.
         * @param window, text The window where to draw, the text we want to display.
         */
        virtual void drawTextPro(const std::string &colorName, unsigned int fontSize, float x, float y,
                                 const std::string &initialText) = 0;

        /**
         * @brief Draw a sprite like a pro in SFMl.
         * @param window, sprite The window where to draw, the sprite we want to display.
         */
        virtual void
        drawSpritePro(float spriteScaleX, float spriteScaleY, float x, float y, const std::string &texturePath) = 0;

        /**
         * @brief Draw a sprite like a pro in SFMl.
         * @param window, rect The window where to draw, the rect we want to display.
         */
        virtual void drawRectPro(float rectSizeX, float rectSizeY, float x, float y, float outlineThickness,
                                 const std::string &lineColor,
                                 const std::string &fillColor, const std::string &texturePath) = 0;

        /**
         * @brief Return the sf::RGB corresponding to the colorName param.
         * @param colorName The color we want to get into SFML.
         */
        virtual sf::Color getColorFromString(const std::string &colorName) = 0;
    };
}
