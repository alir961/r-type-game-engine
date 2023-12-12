/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../AEntity.hpp"

/**
 * @brief Base class for game weapons.
 */
class AWeapon : public AEntity {
public:
    /**
     * @brief Constructor for a Weapon.
     */
    AWeapon(int damage, int speed) : _damage(damage) {
        setSpeed(speed);
    }
    /**
     * @brief Set the damage inflicted by the weapon.
     * @param damage The damage inflicted by the weapon.
     */
    void setDamage(int damage) {
        _damage = damage;
    }

    /**
     * @brief Get the damage inflicted by the weapon.
     * @return The damage inflicted by the weapon.
     */
    int getDamage() {
        return _damage;
    }

private:
    int _damage; /**< Damage inflicted by the weapon. */
};
