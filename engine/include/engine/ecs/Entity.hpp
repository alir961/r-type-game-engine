/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include "./component/ComponentType.hpp"
#include "engine/tools/Split.hpp"
#include <iostream>
#include <unordered_map>
#include <memory>
#include <vector>

namespace RType {

    /**
    * @brief Entity class representing an object in the system.
    */

    enum class Direction {
        LEFT,
        RIGHT,
        DOWN,
        UP,
    };
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
                    &typeid(SizeRectComponent),
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

        bool move(Direction direction, const std::vector<std::shared_ptr<Entity>> &entities,  float windowsWidth, float windowsHeight) {
            switch (direction) {
                case Direction::LEFT:
                    return moveLeft(entities);
                case Direction::RIGHT:
                    return moveRight(entities, windowsWidth);
                case Direction::DOWN:
                    return moveDown(entities, windowsHeight);
                case Direction::UP:
                    return moveUp(entities);
            }
            return false;
        };

        bool canShoot(const std::vector<std::shared_ptr<Entity>> &entities, const std::string &name) {
            if (getEntity(entities, name) == nullptr)
                return true;
            return false;
        }

        void setEntityName(const std::string &name) {_entityName = name;};

        std::string getEntityName() {return _entityName;};

    private:
        std::unordered_map<ComponentType, std::shared_ptr<AComponent>> _components; /**< Map to store component associated with the _entity. */
        std::string _entityName;

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
            } else if constexpr (std::is_same_v<T, SizeRectComponent>) {
                return ComponentType::SizeRect;
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

        bool hit(const std::shared_ptr<Entity> &entity) {
            const auto& [thisX, thisY] = getComponent<PositionComponent>()->getPositions();
            const auto& [thisWidth, thisHeight] = getComponent<SizeComponent>()->getSize();
            const auto& [thisRectWidth, thisRectHeight] = getComponent<SizeRectComponent>()->getSize();
            float thisActualWidth = thisWidth * thisRectWidth;
            float thisActualHeight = thisHeight * thisRectHeight;
            const auto& [entityX, entityY] = entity->getComponent<PositionComponent>()->getPositions();
            const auto& [entityWidth, entityHeight] = entity->getComponent<SizeComponent>()->getSize();
            const auto& [entityRectWidth, entityRectHeight] = entity->getComponent<SizeRectComponent>()->getSize();
            float entityActualWidth = entityWidth * entityRectWidth;
            float entityActualHeight = entityHeight * entityRectHeight;

            if (this == entity.get()) {
                return false;
            }
            return (thisX < entityX + entityActualWidth &&
                    thisX + thisActualWidth > entityX &&
                    thisY < entityY + entityActualHeight &&
                    thisY + thisActualHeight > entityY);
        }


        bool hits(const std::vector<std::shared_ptr<Entity>>& entities) {
            for (const auto& entity : entities) {
                if (hit(entity)) {
                    return true;
                }
            }
            return false;
        }

        bool moveLeft(const std::vector<std::shared_ptr<Entity>> &entities) {
            auto speed = static_cast<float>(getComponent<SpeedComponent>()->getSpeed());
            const auto &[x, y] = getComponent<PositionComponent>()->getPositions();

            if (x - speed < 0 || hits(entities))
                return false;
            getComponent<PositionComponent>()->setPositions(std::make_pair(x - speed, y));
            return true;
        };

        bool moveRight(const std::vector<std::shared_ptr<Entity>> &entities, float windowsWidth) {
            auto speed = static_cast<float>(getComponent<SpeedComponent>()->getSpeed());
            const auto &[x, y] = getComponent<PositionComponent>()->getPositions();
            float size = getComponent<SizeComponent>()->getSize().second;
            float rect = getComponent<SizeRectComponent>()->getSize().second;
            float entitySize = size * rect;
            float entityX = x + entitySize;

            if (entityX + speed > windowsWidth || hits(entities))
                return false;
            getComponent<PositionComponent>()->setPositions(std::make_pair(x + speed, y));
            return true;
        };

        bool moveDown(const std::vector<std::shared_ptr<Entity>> &entities, float windowsHeight) {
            auto speed = static_cast<float>(getComponent<SpeedComponent>()->getSpeed());
            const auto &[x, y] = getComponent<PositionComponent>()->getPositions();
            float size = getComponent<SizeComponent>()->getSize().second;
            float rect = getComponent<SizeRectComponent>()->getSize().second;
            float entitySize = size * rect;
            float entityY = y + entitySize;

            if (entityY + speed > windowsHeight || hits(entities))
                return false;
            getComponent<PositionComponent>()->setPositions(std::make_pair(x, y + speed));
            return true;
        };

        bool moveUp(const std::vector<std::shared_ptr<Entity>> &entities) {
            auto speed = static_cast<float>(getComponent<SpeedComponent>()->getSpeed());
            const auto &[x, y] = getComponent<PositionComponent>()->getPositions();

            if (y - speed < 0 || hits(entities))
                return false;
            getComponent<PositionComponent>()->setPositions(std::make_pair(x, y - speed));
            return true;
        };

        std::shared_ptr<Entity> getEntity(const std::vector<std::shared_ptr<Entity>> &entities, const std::string &name) {
            std::string id = Split::split(_entityName, " ")[1];

            for (const auto& entity : entities) {
                const std::vector<std::string> splitName = Split::split(entity->getEntityName(), " ");

                if (splitName[0] == name && id == splitName[1])
                    return entity;
            }
            return nullptr;
        }
        
    };

    using EntityPtr = std::shared_ptr<Entity>;

}
