/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../ADamageable.hpp"

/**
 * @brief Class representing a starship entity.
 */
class Starship : public ADamageable {
public:
    /**
     * @brief Constructor for Starship.
     * @param isPlayer True if the starship is controlled by a player, false otherwise.
     */
    Starship(bool isPlayer) : _health(100), _speed(10), _isPlayer(isPlayer) {}
};
