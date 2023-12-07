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
    void getHealth() {
        return _health;
    }
    void getIsPlayer() {
        return _isPlayer;
    }
private:
    int _health;
    bool _isPlayer;
};
