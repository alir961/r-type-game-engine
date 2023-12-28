/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GraphicEntity.hpp
*/

#pragma once
#include "AGraphicEntity.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include "../ecs/Entity.hpp"
#include "../ResourceManager.hpp"

namespace RType {
    /**
     * @brief Graphic Entity class from the abstract AGraphicEntity.
     */
    class GraphicEntity : public AGraphicEntity {
    public:
        /**
         * @brief Construct a new Graphic Entity object.
         * @param entity Reference to the ECS entity associated with this graphic entity.
         * @param path Path to the texture file for this graphic entity.
         */
        explicit GraphicEntity(std::shared_ptr<Entity> &entity, const std::string &path);

        /**
         * @brief Update the graphic entity based on the state of the ECS entity.
         * @param deltaTime Time since last update.
         */
        void update(float deltaTime) override;

        /**
         * @brief Draw the graphic entity to the provided window.
         * @param window The window to draw the entity on.
         */
        void draw(sf::RenderWindow &window) override;

        std::shared_ptr<Entity> getEntity() override {
            return entity;
        }

        sf::Sprite getSprite() override {
            return sprite;
        }

    private:
        std::shared_ptr<Entity> entity; /**< Reference to the ECS entity. */
        sf::Sprite sprite; /**< Sprite of the graphical entity. */
        sf::IntRect currentFrame; /**< Current frame of the graphical entity. */
        float animationTime; /**< Animation time accumulator. */
        float animationSpeed; /**< Speed of the animation. */
    };
}
