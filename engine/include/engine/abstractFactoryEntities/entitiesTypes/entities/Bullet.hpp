/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../AWeapon.hpp"

/**
 * @brief Class representing a bullet entity.
 */
class Bullet : public AWeapon {
public:
    /**
     * @brief Constructor for Bullet.
     */
    Bullet() : _damage(25), _speed(20) {}
};
