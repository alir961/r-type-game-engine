/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../AWeapon.hpp"

class Bullet : public AWeapon {
public:
    Bullet() : _damage(25), _speed(20) {}
};
