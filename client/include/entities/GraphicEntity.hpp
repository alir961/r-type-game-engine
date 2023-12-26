/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** IGraphicEntity.hpp
*/

#pragma once
#include "AGraphicEntity.hpp"
#include <SFML/Graphics.hpp>

namespace RType {
    /**
    * @brief Graphic Entity class from the abstract AGraphicEntity.
    */
    class GraphicEntity : public AGraphicEntity {
    public:
        /**
        * @brief Construct a new Graphic Bullet object
        * @param entity Reference to the ECS entity associated with this graphic entity
        */
        explicit GraphicEntity(std::shared_ptr<Entity> &entity);

        /**
        * @brief Update the graphic entity based on the state of the ECS entity
        * @param deltaTime Time since last update
        */
        void update(float deltaTime) override;

        /**
        * @brief Draw the graphic entity to the provided window
        * @param window The window to draw the entity on
        */
        void draw(sf::RenderWindow &window) override;

        std::shared_ptr<Entity> getEntity() override {
            return entity;
        }

        sf::Sprite getSprite() override {
            return sprite;
        }

    private:
        std::shared_ptr<Entity> &entity;
        sf::Sprite sprite;
        sf::IntRect currentFrame;
        float animationTime;
        float animationSpeed;
    };
}
