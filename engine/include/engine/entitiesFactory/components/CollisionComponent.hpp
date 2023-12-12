/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

/**
 * @brief Base class for colliding component.
 */
class CollisionComponent {
public:
    /**
     * @brief Base constructor for collidable component.
     * @param isCollidable The status of the entity (collidable or not).
     */
    CollisionComponent(bool isCollidable) : _isCollidable(isCollidable) {}

    /**
     * @brief Set the collision status of the entity.
     * @param isCollidable True if the entity is collidable, false otherwise.
     */
    void setColliding(bool isCollidable) {
        _isCollidable = isCollidable;
    }

    /**
     * @brief Get the collision status of the entity.
     * @return True if the entity is collidable, false otherwise.
     */
    bool getColliding() {
        return _isCollidable;
    }

private:
    bool _isCollidable; /**< Collision status of the entity. */
};
