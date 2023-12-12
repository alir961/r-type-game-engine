/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <map>

/**
 * @brief Base class for game entities.
 */
class AEntity {
public:
    /**
     * @brief Set the position of the entity.
     * @param position A map representing the position coordinates.
     */
    void setPositions(std::map<int, int> position) {
        _position = position;
    }

    /**
     * @brief Set the speed of the entity.
     * @param speed The speed of the entity.
     */
    void setSpeed(int speed) {
        _speed = speed;
    }

    /**
     * @brief Set the colliding status of the entity.
     * @param isColliding True if the entity is colliding, false otherwise.
     */
    void setColliding(bool isColliding) {
        _isColliding = isColliding;
    }

    /**
     * @brief Get the position of the entity.
     * @return A map representing the position coordinates.
     */
    std::map<int, int> getPositions() {
        return _position;
    }

    /**
     * @brief Get the speed of the entity.
     * @return The speed of the entity.
     */
    int getSpeed() {
        return _speed;
    }

    /**
     * @brief Get the colliding status of the entity.
     * @return True if the entity is colliding, false otherwise.
     */
    bool getColliding() {
        return _isColliding;
    }

private:
    int _speed; /**< Speed of the entity. */
    std::map<int, int> _position; /**< Position of the entity. */
    bool _isColliding; /**< Colliding status of the entity. */
};
