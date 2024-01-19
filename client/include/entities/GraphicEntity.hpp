/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GraphicEntity.hpp
*/

#pragma once

#include "AGraphicEntity.hpp"
#include "../resources/ResourceManager.hpp"
#include "engine/modules/ModuleProvider.hpp"
#include <memory>

namespace RType {

    /**
     * @brief Graphic Entity class from the abstract AGraphicEntity.
     */
    class GraphicEntity : public AGraphicEntity {
    private:
        EntityPtr _entity; /**< Reference to the ECS _entity. */
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        TextComponent _playerName = _module->createText("");
        SpriteComponent _playerSprite = _module->createSprite("client/assets/sprites/r-typesheet42.gif"); /**< Sprite of the graphical _entity. */
        float _animationTime = 0.0F; /**< Animation time accumulator. */
        float _animationSpeed = 0.1F; /**< Speed of the animation. */

    public:
        /**
         * @brief Construct a new Graphic Entity object.
         * @param entity Reference to the ECS _entity associated with this graphic _entity.
         * @param path Path to the texture file for this graphic _entity.
         * @param animationModule Pointer to the IAnimation Module.
         */
        explicit GraphicEntity(EntityPtr &entity, const std::string &entityName);

        /**
         * @brief Update the graphic _entity based on the state of the ECS _entity.
         * @param deltaTime Time since last update.
         */
        void update(float deltaTime) override;

        /**
         * @brief Draw the graphic _entity to the provided window.
         * @param window The window to draw the _entity on.
         */
        void draw() override;

        void moveLeft() override;

        void moveRight() override;

        void moveUp() override;

        void moveDown() override;

        /**
         * @brief get Entity.
         */
        EntityPtr getEntity() override {
            return _entity;
        }

        SpriteComponent getSprite() override {
            return _playerSprite;
        }
    };

}
