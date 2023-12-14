/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include "./components/IComponent.hpp"
#include <iostream>
#include <typeinfo>
#include <unordered_map>

/**
 * @brief Entity class representing an object in the system.
 */
class Entity {
public:
    /**
     * @brief Get a component of a specific type associated with this entity.
     * @tparam T Type of the component.
     * @return Pointer to the component if found, nullptr otherwise.
     */
    template <typename T>
    T* getComponent() const {
        auto it = components.find(typeid(T).hash_code());
        if (it != components.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }

    /**
     * @brief Add a component to the entity.
     * @tparam T Type of the component.
     * @tparam Args Types of the arguments passed to the component constructor.
     * @param args Arguments to pass to the component constructor.
     * @return Pointer to the newly created component if added, nullptr if the component already exists.
     */
    template <typename T, typename... Args>
    T* addComponent(Args&&... args) {
        if (getComponent<T>() == nullptr) {
            T* component = new T(std::forward<Args>(args)...);
            components[typeid(T).hash_code()] = component;
            return component;
        }
        return nullptr;
    }

    /**
     * @brief Remove a component of a specific type from the entity.
     * @tparam T Type of the component to remove.
     */
    template <typename T>
    void removeComponent() {
        auto it = components.find(typeid(T).hash_code());
        if (it != components.end()) {
            delete it->second;
            components.erase(it);
        }
    }

    /**
     * @brief Update all components associated with the entity.
     */
    void updateComponents() {
        for (auto& pair : components) {
            pair.second->update();
        }
    }

    /**
     * @brief Destructor for the entity, cleaning up all associated components.
     */
    ~Entity() {
        for (auto& pair : components) {
            delete pair.second;
        }
    }

private:
    std::unordered_map<std::size_t, IComponent*> components; /**< Map to store components associated with the entity. */
};
