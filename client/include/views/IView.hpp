/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "IDrawable.hpp"

namespace RType {

    class IView : public IDrawable {
    public:
        virtual void update() = 0;

        /**
         * @brief Pure virtual function for drawing objects on an SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the objects.
         * @param entities A vector of shared pointers to AGraphicEntity objects to be drawn.
         */
        void draw(sf::RenderWindow &window, std::vector<GraphicEntityPtr> entities) override = 0;
    };

}