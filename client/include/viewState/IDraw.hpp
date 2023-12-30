/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "../entities/AGraphicEntity.hpp"
#include <memory>

namespace RType {
    /**
     * @class IDraw
     * @brief Interface for objects that can be drawn on an SFML RenderWindow.
     */
    class IDraw {
    public:
        /**
         * @brief Pure virtual function for drawing objects on an SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the objects.
         * @param entities A vector of shared pointers to AGraphicEntity objects to be drawn.
         */
        virtual void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>>) = 0;

        /**
         * @brief Virtual destructor for the IDraw interface.
         */
        virtual ~IDraw() = default;
    };
}
