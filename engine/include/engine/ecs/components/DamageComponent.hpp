/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include "./AComponent.hpp"

/**
 * @brief Base class for damage component.
 */
class DamageComponent : public AComponent {
public:
    /**
     * @brief Base constructor for damager component.
     * @param damage The damage of the entity.
     */
    DamageComponent(int damage) : _damage(damage) {}

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
