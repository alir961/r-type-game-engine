/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "engine/ecs/Entity.hpp"
#include "engine/ecs/EntityManager.hpp"

namespace RType {

    class EntityFactory {
    private:
        EntityManager *_manager;

    public:
        /**
         * Initialize an EntityFactory to instantiate entities
         *
         * @param manager The responsible manager for entities
         */
        explicit EntityFactory(EntityManager *manager) : _manager(manager) {};

        /**
         * Instantiate a default player with default components
         *
         * @return A shared pointer to the created player
         */
        [[nodiscard]] EntityPtr createDefaultPlayer(const std::string &playerName) {
            EntityPtr playerEntity = _manager->createEntity();

            playerEntity->addComponent<SpeedComponent>(10);
            playerEntity->addComponent<HealthComponent>(4200);
            playerEntity->addComponent<PositionComponent>(std::make_pair(300, 30));
            playerEntity->addComponent<SizeComponent>(2.0f, 2.0f);
            playerEntity->addComponent<PlayerComponent>(true);
            playerEntity->addComponent<SizeRectComponent>(33.0f, 15.0f);
            playerEntity->getComponent<PlayerComponent>()->setUserName(playerName);
            playerEntity->getComponent<PlayerComponent>()->setScore(0);
            return playerEntity;
        }

        /**
         * Instantiate a default player with default components
         *
         * @return A shared pointer to the created player
         */
        [[nodiscard]] EntityPtr createBulletPlayer(float startX, float startY) {
            EntityPtr bulletEntity = _manager->createEntity();

            bulletEntity->addComponent<RType::SpeedComponent>(10);
            bulletEntity->addComponent<RType::DamageComponent>(150);
            bulletEntity->addComponent<RType::PositionComponent>(std::make_pair(startX, startY));
            bulletEntity->addComponent<RType::SizeComponent>(1.0f, 1.0f);
            bulletEntity->addComponent<SizeRectComponent>(14.0f, 14.0f);
            return bulletEntity;
        }

        /**
         * Instantiate a default monster with default components
         *
         * @return A shared pointer to the created ùonster
         */
        [[nodiscard]] EntityPtr createMonster(float startX, float startY) {
            EntityPtr monsterEntity = _manager->createEntity();

            monsterEntity->addComponent<RType::SpeedComponent>(2);
            monsterEntity->addComponent<RType::HealthComponent>(500);
            monsterEntity->addComponent<RType::PositionComponent>(std::make_pair(startX, startY));
            monsterEntity->addComponent<RType::SizeComponent>(1.0f, 1.0f);
            monsterEntity->addComponent<SizeRectComponent>(33.0f, 33.0f);
            return monsterEntity;
        }
        /**
         * Instantiate a default static entity with default components
         *
         * @return A shared pointer to the created static entity
         */
        [[nodiscard]] EntityPtr createStatic(float startX, float startY) {
            EntityPtr monsterEntity = _manager->createEntity();

            monsterEntity->addComponent<RType::PositionComponent>(std::make_pair(startX, startY));
            monsterEntity->addComponent<RType::SizeComponent>(1.0f, 1.0f);
            monsterEntity->addComponent<SizeRectComponent>(122.0f, 122.0f);
            return monsterEntity;
        }

        [[nodiscard]] EntityPtr createStarship(float startX, float startY) {
            EntityPtr starshipEntity = _manager->createEntity();

            starshipEntity->addComponent<SpeedComponent>(5);
            starshipEntity->addComponent<HealthComponent>(3000);
            starshipEntity->addComponent<PositionComponent>(std::make_pair(startX, startY));
            starshipEntity->addComponent<SizeComponent>(2.0f, 2.0f);
            starshipEntity->addComponent<SizeRectComponent>(32.0f, 22.0f);
            return starshipEntity;
        }

        [[nodiscard]] EntityPtr createBulletStarship(float startX, float startY) {
            EntityPtr bulletEntity = _manager->createEntity();

            bulletEntity->addComponent<RType::SpeedComponent>(7);
            bulletEntity->addComponent<RType::DamageComponent>(300);
            bulletEntity->addComponent<RType::PositionComponent>(std::make_pair(startX, startY));
            bulletEntity->addComponent<RType::SizeComponent>(1.0f, 1.0f);
            bulletEntity->addComponent<SizeRectComponent>(32.0f, 28.0f);
            return bulletEntity;
        }
    };

}
