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
    Starship(bool isPlayer) : ADamageable(100, isPlayer, 10) {}
};
