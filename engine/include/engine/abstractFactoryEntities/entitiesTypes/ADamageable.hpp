/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../AEntity.hpp"

/**
 * @brief Base class for damageable game entities.
 */
class ADamageable : public AEntity {
public:
    /**
     * @brief Constructor for Damageable entity.
     */
    ADamageable(int health, bool isPlayer, int speed) : _health(health), _isPlayer(isPlayer) {
        setSpeed(speed);
    }
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

    /**
     * @brief Check if the damageable entity is controlled by a player.
     * @return True if the entity is controlled by a player, false otherwise.
     */
    bool getIsPlayer() {
        return _isPlayer;
    }

private:
    int _health; /**< Health of the damageable entity. */
    bool _isPlayer; /**< Flag indicating if the entity is controlled by a player. */
};
