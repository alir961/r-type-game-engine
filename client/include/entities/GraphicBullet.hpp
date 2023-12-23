/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GraphicBullet.hpp
*/

#pragma once
#include "IGraphicEntity.hpp"
#include "engine/ecs/Entity.hpp"
#include "engine/ecs/component/PositionComponent.hpp"
#include <SFML/Graphics.hpp>

class GraphicBullet : public IGraphicEntity {
public:
    /**
         * @brief Construct a new Graphic Bullet object
         *
         * @param entity Reference to the ECS entity associated with this graphic entity
         */
    explicit GraphicBullet(std::shared_ptr<Entity> &entity);

    /**
         * @brief Update the graphic entity based on the state of the ECS entity
         *
         * @param deltaTime Time since last update
         */
    void update(float deltaTime) override;

    /**
         * @brief Draw the graphic entity to the provided window
         *
         * @param window The window to draw the entity on
         */
    void draw(sf::RenderWindow &window) override;

private:
    std::shared_ptr<Entity> &entity;
    sf::Sprite sprite;
    sf::IntRect currentFrame;
    float animationTime;
    float animationSpeed;
};
