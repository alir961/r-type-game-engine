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
class CollidingComponent {
public:
    /**
     * @brief Base constructor for colliding component.
     * @param isColliding The status of the entity (collidable or not).
     */
    CollidingComponent(bool isColliding) : _isColliding(isColliding) {}

    /**
     * @brief Set the colliding status of the entity.
     * @param isColliding True if the entity is colliding, false otherwise.
     */
    void setColliding(bool isColliding) {
        _isColliding = isColliding;
    }

    /**
     * @brief Get the colliding status of the entity.
     * @return True if the entity is colliding, false otherwise.
     */
    bool getColliding() {
        return _isColliding;
    }

private:
    bool _isColliding; /**< Colliding status of the entity. */
};
