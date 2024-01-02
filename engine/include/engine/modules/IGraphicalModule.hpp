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
    };
}
