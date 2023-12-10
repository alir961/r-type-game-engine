/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../AEntity.hpp"

class ADamageable : public AEntity {
public:
    void setHealth(int health) {
        _health = health;
    }
    int getHealth() {
        return _health;
    }
    bool getIsPlayer() {
        return _isPlayer;
    }
protected:
    int _health;
    bool _isPlayer;
};
