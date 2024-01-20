/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** IGraphicEntity.hpp
*/

#pragma once
#include "engine/ecs/Entity.hpp"
#include "engine/ecs/component/PositionComponent.hpp"
#include "engine/modules/graphical/IGraphicalModule.hpp"
#include "engine/modules/animation/IAnimationModule.hpp"
#include <SFML/Graphics.hpp>

namespace RType {
    /**
    * @brief Graphic Entity interface.
    */
    class IGraphicEntity {
    public:
        virtual ~IGraphicEntity() = default;

        /**
        * @brief Update the graphic _entity based on the game state
        * @param deltaTime Time since last update
        */
        virtual void update(float deltaTime) = 0;

        /**
        * @brief Draw the graphic _entity to the provided window
        * @param window The window to draw the _entity on
        */
        virtual void draw() = 0;

        /**
        * @brief Draw the graphic _entity to the provided window
        * @param sprite The _entitySprite to move
        * @param entity The _entity to move
        */
        virtual void moveLeft() = 0;

        /**
        * @brief Draw the graphic _entity to the provided window
        * @param sprite The _entitySprite to move
        * @param entity The _entity to move
        */
        virtual void moveRight() = 0;

        /**
        * @brief Draw the graphic _entity to the provided window
        * @param sprite The _entitySprite to move
        * @param entity The _entity to move
        */
        virtual void moveUp() = 0;

        /**
        * @brief Draw the graphic _entity to the provided window
        * @param sprite The _entitySprite to move
        * @param entity The _entity to move
        */
        virtual void moveDown() = 0;
    };
}
