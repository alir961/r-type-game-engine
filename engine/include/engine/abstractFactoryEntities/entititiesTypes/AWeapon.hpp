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
    void getDamage() {
        return _damage;
    }
private:
    int _damage;
};