/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../AEntity.hpp"

class AWeapon : public AEntity {
public:
    void setDamage(int damage) {
        _damage = damage;
    }
    int getDamage() {
        return _damage;
    }
protected:
    int _damage;
};