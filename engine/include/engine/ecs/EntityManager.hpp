/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include "Entity.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

namespace RType {

    /**
    * @brief EntityManager class responsible for managing entities in the system.
    */
    class EntityManager {
    public:
        /**
        * @brief Create a new _entity and add it to the EntityManager.
        * @return Shared pointer to the created _entity.
        */
        std::shared_ptr<Entity> createEntity() {
            std::shared_ptr<Entity> entity = std::make_shared<Entity>();
            _entities.push_back(entity);
            return entity;
        }

        /**
        * @brief Destroy an _entity and remove it from the EntityManager.
        * @param entity Shared pointer to the _entity to destroy.
        */
        void destroyEntity(std::shared_ptr<Entity> entity) {
            auto it = std::find(_entities.begin(), _entities.end(), entity);
            if (it != _entities.end()) {
                _entities.erase(it);
            }
        }

        /**
        * @brief Update all entities in the EntityManager.
        */
        void updateEntities() {
            for (const auto &entity: _entities) {
                entity->updateComponents();
            }
        }

        /**
        * @brief Destructor for the EntityManager, cleaning up all associated entities.
        */
        ~EntityManager() = default;

    private:
        std::vector<std::shared_ptr<Entity>> _entities; /**< Vector to store entities managed by the EntityManager. */
    };
}
