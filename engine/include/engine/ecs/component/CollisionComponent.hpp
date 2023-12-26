/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include "./AComponent.hpp"

namespace RType {
    /**
     * @brief Base class for collision component.
    */
    class CollisionComponent : public AComponent {
    public:
        /**
         * @brief Base constructor for collidable component.
        * @param isCollidable The status of the entity (collidable or not).
        */
        explicit CollisionComponent(bool isCollidable) : _isCollidable(isCollidable) {}

        /**
        * @brief Set the collision status of the entity.
        * @param isCollidable True if the entity is collidable, false otherwise.
        */
        void setCollision(bool isCollidable) {
            _isCollidable = isCollidable;
        }

        /**
        * @brief Get the collision status of the entity.
        * @return True if the entity is collidable, false otherwise.
        */
        [[nodiscard]] bool getCollisionStatus() const {
            return _isCollidable;
        }

        /**
        * @brief Update the component.
        */
        void update() override {
            std::cout << "Component update\n";
        }

    private:
        bool _isCollidable; /**< Collision status of the entity. */
    };
}
