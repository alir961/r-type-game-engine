/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GraphicEntity.hpp
*/

#pragma once

#include "AGraphicEntity.hpp"
#include "engine/modules/ModuleProvider.hpp"
#include <memory>

namespace RType {

    /**
     * @brief Graphic Entity class from the abstract AGraphicEntity.
     */
    class GraphicEntity : public AGraphicEntity {
    private:
        EntityPtr _entity; /**< Reference to the ECS _entity. */
        ModuleProviderPtr _provider = ModuleProvider::getInstance();
        IGraphicalModule *_module = _provider->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        IAnimationModule *_animation = _provider->loadAndGetModule<IAnimationModule>(ModuleType::ANIMATION);
        TextComponent _entityNameText = _module->createText("");
        SpriteComponent _entitySprite; /**< Sprite of the graphical _entity. */
        float _animationTime = 0.0F; /**< Animation time accumulator. */
        float _animationSpeed = 0.1F; /**< Speed of the animation. */

    public:
        /**
         * @brief Construct a new Graphic Entity object.
         * @param entity Reference to the ECS _entity associated with this graphic _entity.
         * @param path Path to the texture file for this graphic _entity.
         * @param animationModule Pointer to the IAnimation Module.
         */
        explicit GraphicEntity(EntityPtr entity, const std::string &path, const std::string &entityName);

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
            return _entitySprite;
        }
    };

}
