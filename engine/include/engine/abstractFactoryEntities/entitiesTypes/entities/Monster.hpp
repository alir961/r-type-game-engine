/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../ADamageable.hpp"

/**
 * @brief Class representing a monster entity.
 */
class Monster : public ADamageable {
public:
    /**
     * @brief Constructor for Monster.
     */
    Monster() : _health(200), _speed(10) {}
};
