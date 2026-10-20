/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GraphicEntity.hpp
*/

#pragma once

#include "AGraphicEntity.hpp"
#include "../components/Ui.hpp"
#include "../components/Effects.hpp"
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
        IAnimationModule *_animationModule = _provider->loadAndGetModule<IAnimationModule>(ModuleType::ANIMATION);
        AnimationPtr _animation; /**< Animation owned by this entity only. */
        std::string _animationName; /**< Entity type the animation was built for (e.g. "redPlayer"). */
        Label _entityNameText = Label("", 22, Theme::Text, 0.0F, 0.0F, Align::CENTER);
        RectShape _healthBackground = _module->createRectShape();
        RectShape _healthFill = _module->createRectShape();
        RectShape _hitbox = _module->createRectShape();
        SpriteComponent _entitySprite; /**< Sprite of the graphical _entity. */
        float _animationTime = 0.0F; /**< Animation time accumulator. */
        float _hitFlashTime = 0.0F; /**< Remaining time of the red flash shown when hit. */
        int _initialHealth = 0;
        int _lastHealth = 0;

        /**
         * @brief Rebuild the animation when the entity type changes (a player switching color).
         */
        void refreshAnimation();

        /**
         * @brief Engine exhaust for ships, sparks when hit.
         */
        void emitParticles(bool wasHit);

    public:
        static inline bool showHitboxes = false; /**< Outline the server hitboxes (console command "hitbox"). */

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

        void drawHealthBar();

        /**
         * @brief Center of the entity on screen, used to place effects.
         */
        [[nodiscard]] Vector2f getCenter() const;

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
