/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include "./component/ComponentType.hpp"
#include <iostream>
#include <unordered_map>
#include <memory>

namespace RType {

    /**
    * @brief Entity class representing an object in the system.
    */
    class Entity {
    public:
        /**
        * @brief Get a component of a specific type associated with this _entity.
        * @tparam T Type of the component.
        * @return Shared pointer to the component if found, nullptr otherwise.
        */
        template<typename T>
        std::shared_ptr<T> getComponent() const {
            auto component = _components.find(getComponentType<T>());
            if (component != _components.end()) {
                return std::dynamic_pointer_cast<T>(component->second);
            }
            return nullptr;
        }

        /**
        * @brief Add a component to the _entity.
        * @tparam T Type of the component.
        * @tparam Args Types of the arguments passed to the component constructor.
        * @param args Arguments to pass to the component constructor.
        * @return Shared pointer to the newly created component if added, nullptr if the component already exists.
        */
        template<typename T, typename... Args>
        std::shared_ptr<T> addComponent(Args &&...args) {
            if (getComponent<T>() == nullptr) {
                std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
                _components[getComponentType<T>()] = component;
                return component;
            }
            return nullptr;
        }

        /**
        * @brief Remove a component of a specific type from the _entity.
        * @tparam T Type of the component to remove.
        */
        template<typename T>
        void removeComponent() {
            auto component = _components.find(getComponentType<T>());
            if (component != _components.end()) {
                _components.erase(component);
            }
        }

        /**
        * @brief Update all component associated with the _entity.
        */
        void updateComponents() {
            for (auto &pair: _components) {
                pair.second->update();
            }
        }

        /**
        * @brief Check if the _entity has a set of base components.
        * @return True if all specified components are present, false otherwise.
        */
        bool hasBaseComponents() const {
            bool allComponentsPresent = true;
            const std::type_info *componentTypes[] = {
                    &typeid(SpeedComponent),
                    &typeid(HealthComponent),
                    &typeid(PositionComponent),
                    &typeid(SizeComponent),
                    &typeid(PlayerComponent)
            };
            for (const auto *type : componentTypes) {
                bool hasComponent = false;
                for (const auto &pair : _components) {
                    const std::type_info &currentType = typeid(*(pair.second));
                    if (currentType == *type) {
                        hasComponent = true;
                        break;
                    }
                }
                if (!hasComponent) {
                    allComponentsPresent = false;
                    std::cout << "Entity doesn't have the required component: " << type->name() << std::endl;
                    break;
                }
            }
            return allComponentsPresent;
        }

        /**
        * @brief Return true if the _entity has components, false otherwise.
        */
        bool hasComponents() const {
            return !_components.empty();
        }

        /**
        * @brief Destructor for the _entity, cleaning up all associated component.
        */
        ~Entity() = default;

    private:
        std::unordered_map<ComponentType, std::shared_ptr<AComponent>> _components; /**< Map to store component associated with the _entity. */

        /**
        * @brief Get the component type enum value for a specific component type.
        * @tparam T Type of the component.
        * @return ComponentType enum value.
        */
        template<typename T>
        ComponentType getComponentType() const {
            if constexpr (std::is_same_v<T, SizeComponent>) {
                return ComponentType::Size;
            } else if constexpr (std::is_same_v<T, DamageComponent>) {
                return ComponentType::Damage;
            } else if constexpr (std::is_same_v<T, HealthComponent>) {
                return ComponentType::Health;
            } else if constexpr (std::is_same_v<T, PlayerComponent>) {
                return ComponentType::Player;
            } else if constexpr (std::is_same_v<T, PositionComponent>) {
                return ComponentType::Position;
            } else if constexpr (std::is_same_v<T, SpeedComponent>) {
                return ComponentType::Speed;
            }
        }
    };

    using EntityPtr = std::shared_ptr<Entity>;
}
