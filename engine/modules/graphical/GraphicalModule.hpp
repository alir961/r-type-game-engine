/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "engine/modules/graphical/IGraphicalModule.hpp"

namespace RType {

    using WindowPtr = std::shared_ptr<sf::RenderWindow>;

    class GraphicalModule : public IGraphicalModule {
    private:
        WindowPtr _window = nullptr;

    public:
        void load() override;
        void unload() override;

        void openWindow(uint32_t width, uint32_t height, std::string title) override;

        void close() override;

        bool isOpen() override;

        void clear() override;

        void display() override;

        bool pollEvent(sf::Event &event) override;

        Vector2f getMousePosition() override;

        bool isMouseClicked() override;

        /**
         * @brief Draw a text in SFML.
         * @param window, text The window where to draw, the text we want to display.
         */
        TextComponent createText(const std::string &text) override;

        RectShape createRectShape() override;

        SpriteComponent createSprite(const std::string &texturePath) override;

        /**
         * @brief Draw a sprite in SFMl.
         * @param window, sprite The window where to draw, the sprite we want to display.
         */
        void drawSprite(sf::Sprite sprite) override;

        /**
         * @brief Draw a sprite in SFMl.
         * @param window, rect The window where to draw, the rect we want to display.
         */
        void drawRect(sf::RectangleShape rect) override;

        /**
         * @brief Draw a text like a pro in SFML.
         * @param window, text The window where to draw, the text we want to display.
         */
        void drawTextPro(const std::string &colorName, unsigned int fontSize, float x, float y,
                         const std::string &initialText) override;

        /**
         * @brief Draw a sprite like a pro in SFMl.
         * @param window, sprite The window where to draw, the sprite we want to display.
         */
        void
        drawSpritePro(float spriteScaleX, float spriteScaleY, float x, float y, const std::string &texturePath) override;

        /**
         * @brief Draw a sprite like a pro in SFMl.
         * @param window, rect The window where to draw, the rect we want to display.
         */
        void drawRectPro(float rectSizeX, float rectSizeY, float x, float y, float outlineThickness,
                         const std::string &lineColor,
                         const std::string &fillColor, const std::string &texturePath) override;

        /**
         * @brief Return the sf::RGB corresponding to the colorName param.
         * @param colorName The color we want to get into SFML.
         */
        sf::Color getColorFromString(const std::string &colorName) override;
    };
}
