/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "../entities/AGraphicEntity.hpp"
#include "../ClientViewport.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace RType {

    /**
     * @class IDrawable
     * @brief Interface for objects that can be drawn on an SFML RenderWindow.
     */
    class IDrawable {
    public:
        /**
         * @brief Pure virtual function for drawing objects on an SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the objects.
         * @param entities A vector of shared pointers to AGraphicEntity objects to be drawn.
         */
        virtual void draw(sf::RenderWindow &window, std::vector<GraphicEntityPtr>) = 0;

        /**
         * @brief Virtual destructor for the IDrawable interface.
         */
        virtual ~IDrawable() = default;
    };
}
