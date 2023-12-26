/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** IGraphicEntity.hpp
*/

#pragma once
#include "engine/ecs/Entity.hpp"
#include "engine/ecs/component/PositionComponent.hpp"
#include <SFML/Graphics.hpp>

/**
 * @brief Graphic Entity interface.
 */
class IGraphicEntity {
public:
    virtual ~IGraphicEntity() = default;

    /**
    * @brief Update the graphic entity based on the game state
    * @param deltaTime Time since last update
    */
    virtual void update(float deltaTime) = 0;

    /**
    * @brief Draw the graphic entity to the provided window
    * @param window The window to draw the entity on
    */
    virtual void draw(sf::RenderWindow &window) = 0;

    /**
    * @brief Draw the graphic entity to the provided window
    * @param sprite The sprite to move
    * @param entity The entity to move
    */
    virtual void moveLeft(sf::Sprite &sprite, std::shared_ptr<Entity> &entity) = 0;
    /**
    * @brief Draw the graphic entity to the provided window
    * @param sprite The sprite to move
    * @param entity The entity to move
    */
    virtual void moveRight(sf::Sprite &sprite, std::shared_ptr<Entity> &entity) = 0;
    /**
    * @brief Draw the graphic entity to the provided window
    * @param sprite The sprite to move
    * @param entity The entity to move
    */
    virtual void moveUp(sf::Sprite &sprite, std::shared_ptr<Entity> &entity) = 0;
    /**
    * @brief Draw the graphic entity to the provided window
    * @param sprite The sprite to move
    * @param entity The entity to move
    */
    virtual void moveDown(sf::Sprite &sprite, std::shared_ptr<Entity> &entity) = 0;
};
