/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** IGraphicEntity.hpp
*/

#pragma once
#include "IGraphicEntity.hpp"

namespace RType {

    /**
    * @brief Graphic Entity abstraction from the interface IGraphicEntity.
    */
    class AGraphicEntity : public IGraphicEntity {
    private:
        const std::string _entityName; /**< Entity name. */

    public:
        explicit AGraphicEntity(std::string entityName) : _entityName(std::move(entityName)) {}

        void moveLeft(sf::Sprite &sprite, EntityPtr &entity) override {
            auto speed = static_cast<float>(entity->getComponent<SpeedComponent>()->getSpeed());
            const auto &[x, y] = entity->getComponent<PositionComponent>()->getPositions();

            sprite.move(-speed, 0.0F);
            entity->getComponent<PositionComponent>()->setPositions(std::make_pair(x - speed, y));
        }

        void moveRight(sf::Sprite &sprite, EntityPtr &entity) override {
            auto speed = static_cast<float>(entity->getComponent<SpeedComponent>()->getSpeed());
            const auto &[x, y] = entity->getComponent<PositionComponent>()->getPositions();
            
            sprite.move(speed, 0.0F);
            entity->getComponent<PositionComponent>()->setPositions(std::make_pair(x + speed, y));
        }

        void moveUp(sf::Sprite &sprite, EntityPtr &entity) override {
            auto speed = static_cast<float>(entity->getComponent<SpeedComponent>()->getSpeed());
            const auto &[x, y] = entity->getComponent<PositionComponent>()->getPositions();
            
            sprite.move(0.0F, -speed);
            entity->getComponent<PositionComponent>()->setPositions(std::make_pair(x, y - speed));
        }

        void moveDown(sf::Sprite &sprite, EntityPtr &entity) override {
            auto speed = static_cast<float>(entity->getComponent<SpeedComponent>()->getSpeed());
            const auto &[x, y] = entity->getComponent<PositionComponent>()->getPositions();
            
            sprite.move(0.0F, speed);
            entity->getComponent<PositionComponent>()->setPositions(std::make_pair(x, y + speed));
        }

        /**
        * @brief Return the _entity of the graphical _entity
        */
        virtual EntityPtr getEntity() = 0;

        /**
        * @brief Return the _sprite of the graphical _entity
        */
        virtual sf::Sprite getSprite() = 0;

        /**
        * @brief Return the name of the graphical _entity
        */
        [[nodiscard]] std::string getEntityName() const {
            return _entityName;
        }

        ~AGraphicEntity() override = default;
    };

    using GraphicEntityPtr = std::shared_ptr<AGraphicEntity>;

}
