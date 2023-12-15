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

/**
 * @brief EntityManager class responsible for managing entities in the system.
 */
class EntityManager {
public:
    /**
     * @brief Create a new entity and add it to the EntityManager.
     * @return Shared pointer to the created entity.
     */
    std::shared_ptr<Entity> createEntity() {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        entities.push_back(entity);
        return entity;
    }

    /**
     * @brief Destroy an entity and remove it from the EntityManager.
     * @param entity Shared pointer to the entity to destroy.
     */
    void destroyEntity(std::shared_ptr<Entity> entity) {
        auto it = std::find(entities.begin(), entities.end(), entity);
        if (it != entities.end()) {
            entities.erase(it);
        }
    }

    /**
     * @brief Update all entities in the EntityManager.
     */
    void updateEntities() {
        for (const auto &entity : entities) {
            entity->updateComponents();
        }
    }

    /**
     * @brief Destructor for the EntityManager, cleaning up all associated entities.
     */
    ~EntityManager() {}

private:
    std::vector<std::shared_ptr<Entity>> entities; /**< Vector to store entities managed by the EntityManager. */
};
