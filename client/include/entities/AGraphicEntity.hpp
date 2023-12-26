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
    public:
        void moveLeft(sf::Sprite &sprite, std::shared_ptr<Entity> &entity) override {
            float speed = entity->getComponent<SpeedComponent>()->getSpeed();
            sprite.move(-speed, 0.0f);

            auto currentPosition = entity->getComponent<PositionComponent>()->getPositions();
            entity->getComponent<PositionComponent>()->setPositions(std::make_pair(
                    currentPosition.first - speed,
                    currentPosition.second));
        }

        void moveRight(sf::Sprite &sprite, std::shared_ptr<Entity> &entity) override {
            float speed = entity->getComponent<SpeedComponent>()->getSpeed();
            sprite.move(speed, 0.0f);

            auto currentPosition = entity->getComponent<PositionComponent>()->getPositions();
            entity->getComponent<PositionComponent>()->setPositions(std::make_pair(
                    currentPosition.first + speed,
                    currentPosition.second));
        }

        void moveUp(sf::Sprite &sprite, std::shared_ptr<Entity> &entity) override {
            float speed = entity->getComponent<SpeedComponent>()->getSpeed();
            sprite.move(0.0f, -speed);

            auto currentPosition = entity->getComponent<PositionComponent>()->getPositions();
            entity->getComponent<PositionComponent>()->setPositions(std::make_pair(
                    currentPosition.first,
                    currentPosition.second - speed));
        }

        void moveDown(sf::Sprite &sprite, std::shared_ptr<Entity> &entity) override {
            float speed = entity->getComponent<SpeedComponent>()->getSpeed();
            sprite.move(0.0f, speed);

            auto currentPosition = entity->getComponent<PositionComponent>()->getPositions();
            entity->getComponent<PositionComponent>()->setPositions(std::make_pair(
                    currentPosition.first,
                    currentPosition.second + speed));
        }

        virtual std::shared_ptr<Entity> getEntity() = 0;
        virtual sf::Sprite getSprite() = 0;
    };
}
