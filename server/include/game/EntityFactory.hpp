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
        [[nodiscard]] EntityPtr createDefaultPlayer() {
            EntityPtr playerEntity = _manager->createEntity();

            playerEntity->addComponent<SpeedComponent>(10);
            playerEntity->addComponent<HealthComponent>(100);
            playerEntity->addComponent<PositionComponent>(std::make_pair(300, 30));
            playerEntity->addComponent<SizeComponent>(2.0f, 2.0f);
            playerEntity->addComponent<PlayerComponent>(true);
            playerEntity->addComponent<SizeRectComponent>(33.0f, 15.0f);
            return playerEntity;
        }
    };

}