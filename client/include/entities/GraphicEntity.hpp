/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GraphicEntity.hpp
*/

#pragma once
#include "AGraphicEntity.hpp"
#include <memory>
#include "../resources/ResourceManager.hpp"
#include "src/engine/modules/AnimationModule.hpp"


namespace RType {
    /**
     * @brief Graphic Entity class from the abstract AGraphicEntity.
     */
    class GraphicEntity : public AGraphicEntity {
    public:
        /**
         * @brief Construct a new Graphic Entity object.
         * @param entity Reference to the ECS _entity associated with this graphic _entity.
         * @param path Path to the texture file for this graphic _entity.
         * @param animationModule Pointer to the Animation Module.
         */
        explicit GraphicEntity(EntityPtr &entity, const std::string path, const std::string entityName, AnimationModule *animationModule);

        /**
         * @brief Update the graphic _entity based on the state of the ECS _entity.
         * @param deltaTime Time since last update.
         */
        void update(float deltaTime) override;

        /**
         * @brief Draw the graphic _entity to the provided window.
         * @param window The window to draw the _entity on.
         */
        void draw(sf::RenderWindow &window, IGraphicalModule *graphicalModule) override;

        /**
         * @brief get Entity.
         */
        EntityPtr getEntity() override {
            return _entity;
        }

        /**
         * @brief get Sprite.
         */
        sf::Sprite getSprite() override {
            return _sprite;
        }

    private:
        EntityPtr _entity; /**< Reference to the ECS _entity. */
        sf::Sprite _sprite; /**< Sprite of the graphical _entity. */
        sf::IntRect _currentFrame; /**< Current frame of the graphical _entity. */
        float _animationTime; /**< Animation time accumulator. */
        float _animationSpeed; /**< Speed of the animation. */
        ResourceManager _resourceManager; /**< Resource Manager instance. */
        AnimationModule* _animationModule;  /**< Animation Module instance. */
    };
}
