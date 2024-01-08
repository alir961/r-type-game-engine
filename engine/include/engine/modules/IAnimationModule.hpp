/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** IAnimationModule.hpp
*/

#pragma once

#include "engine/modules/IModule.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include "engine/ecs/Entity.hpp"

namespace RType {

    class IAnimationModule : public IModule {
    public:
        virtual void load() = 0;
        virtual void unload() = 0;

        /**
         * @brief Initialize animation for a given entity.
         * @param entity The entity for which to initialize animation.
         * @param texturePath The path to the texture file used for animation.
         */
        virtual void initAnimation(std::shared_ptr<Entity> &entity, const std::string &texturePath) = 0;

        /**
         * @brief Update animation for a given entity based on delta time.
         * @param entity The entity for which to update animation.
         * @param deltaTime Time elapsed since the last update.
         */
        virtual void updateAnimation(std::shared_ptr<Entity> &entity, float deltaTime) = 0;

        /**
         * @brief Get the current animation frame for a given entity.
         * @param entity The entity for which to get the current animation frame.
         * @return The current IntRect representing the frame in the sprite sheet.
         */
        virtual sf::IntRect getCurrentFrame(std::shared_ptr<Entity> &entity) = 0;
    };
}
