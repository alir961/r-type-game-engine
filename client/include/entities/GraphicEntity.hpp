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
         * @param animationModule Pointer to the IAnimation Module.
         */
        explicit GraphicEntity(EntityPtr &entity, const std::string &path, const std::string &entityName);

        /**
         * @brief Update the graphic _entity based on the state of the ECS _entity.
         * @param deltaTime Time since last update.
         */
        void update(float deltaTime, IAnimationModule *animationModule) override;

        /**
         * @brief Draw the graphic _entity to the provided window.
         * @param window The window to draw the _entity on.
         */
        void draw(sf::RenderWindow &window, IGraphicalModule *graphicalModule) override;

        void loadSprite(IAnimationModule *animationModule);
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
        float _animationTime = 0.0F; /**< Animation time accumulator. */
        float _animationSpeed = 0.1F; /**< Speed of the animation. */
        ResourceManager _resourceManager; /**< Resource Manager instance. */
        sf::Font _font;
    };
}
