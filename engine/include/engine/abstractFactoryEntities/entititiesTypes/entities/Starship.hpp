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
    Starship() : health(100), speed(10) {

    }
};
