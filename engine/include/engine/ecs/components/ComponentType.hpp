/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "CollisionComponent.hpp"
#include "DamageComponent.hpp"
#include "HealthComponent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "SpeedComponent.hpp"

/**
 * @brief Enum to represent different types of components.
 */
enum class ComponentType {
    Collision,  /**< Component type for collision. */
    Damage,     /**< Component type for damage. */
    Health,     /**< Component type for health. */
    Player,     /**< Component type for playable entity. */
    Position,   /**< Component type for position. */
    Speed       /**< Component type for speed. */
};
