/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include "./AComponent.hpp"

/**
 * @brief Base class for health component.
 */
class HealthComponent : public AComponent {
public:
    /**
     * @brief Base constructor for health component.
     * @param health The health of the entity.
     */
    explicit HealthComponent(int health) : _health(health) {}

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
    [[nodiscard]] int getHealth() const {
        return _health;
    }

    /**
     * @brief Update the component.
     */
    void update() override {
        std::cout << "Component update\n";
    }

private:
    int _health; /**< Health of the damageable entity. */
};
