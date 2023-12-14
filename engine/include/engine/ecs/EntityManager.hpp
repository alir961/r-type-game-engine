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

/**
 * @brief EntityManager class responsible for managing entities in the system.
 */
class EntityManager {
public:
    /**
     * @brief Create a new entity and add it to the EntityManager.
     * @return Pointer to the created entity.
     */
    Entity* createEntity() {
        Entity* entity = new Entity();
        entities.push_back(entity);
        return entity;
    }

    /**
     * @brief Destroy an entity and remove it from the EntityManager.
     * @param entity Pointer to the entity to destroy.
     */
    void destroyEntity(Entity* entity) {
        auto it = std::find(entities.begin(), entities.end(), entity);
        if (it != entities.end()) {
            delete *it;
            entities.erase(it);
        }
    }

    /**
     * @brief Update all entities in the EntityManager.
     */
    void updateEntities() {
        for (Entity* entity : entities) {
            entity->updateComponents();
        }
    }

    /**
     * @brief Destructor for the EntityManager, cleaning up all associated entities.
     */
    ~EntityManager() {
        for (Entity* entity : entities) {
            delete entity;
        }
    }

private:
    std::vector<Entity*> entities; /**< Vector to store entities managed by the EntityManager. */
};
