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
    explicit SpeedComponent(int speed) : _speed(speed) {}

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
    [[nodiscard]] int getSpeed() const {
        return _speed;
    }

    /**
     * @brief Update the component.
     */
    void update() override {
        std::cout << "Component update\n";
    }

private:
    int _speed; /**< Speed of the entity. */
};
