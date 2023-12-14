/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include "./AComponent.hpp"

/**
 * @brief Base class for speed component.
 */
class SpeedComponent : public AComponent {
public:
    /**
     * @brief Base constructor for speed component.
     * @param speed The speed of the entity.
     */
    SpeedComponent(int speed) : _speed(speed) {}

    /**
     * @brief Set the speed of the entity.
     * @param speed The speed of the entity.
     */
    void setSpeed(int speed) {
        _speed = speed;
    }

    /**
     * @brief Get the speed of the entity.
     * @return The speed of the entity.
     */
    int getSpeed() {
        return _speed;
    }

private:
    int _speed; /**< Speed of the entity. */
};
