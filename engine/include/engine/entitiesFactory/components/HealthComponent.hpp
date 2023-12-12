/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

/**
 * @brief Base class for health component.
 */
class HealthComponent {
public:
    /**
     * @brief Constructor for health component.
     * @param health The health of the entity.
     */
    HealthComponent(int health) : _health(health) {}

    /**
     * @brief Set the health of the damageable entity.
     * @param health The health of the damageable entity.
     */
    void setHealth(int health) {
        _health = health;
    }

    /**
     * @brief Get the health of the damageable entity.
     * @return The health of the damageable entity.
     */
    int getHealth() {
        return _health;
    }

private:
    int _health; /**< Health of the damageable entity. */
};
