/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** IGraphicEntity.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>

class IGraphicEntity {
public:
    virtual ~IGraphicEntity() = default;

    /**
         * @brief Update the graphic entity based on the game state
         *
         * @param deltaTime Time since last update
         */
    virtual void update(float deltaTime) = 0;

    /**
         * @brief Draw the graphic entity to the provided window
         *
         * @param window The window to draw the entity on
         */
    virtual void draw(sf::RenderWindow &window) = 0;
};
