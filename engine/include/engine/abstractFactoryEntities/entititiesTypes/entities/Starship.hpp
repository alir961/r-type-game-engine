/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../ADamageable.hpp"

class Starship : public ADamageable {
public:
    Starship(bool isPlayer) : _health(100), _speed(10), _isPlayer(isPlayer) {}
};
