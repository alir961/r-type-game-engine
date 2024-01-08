/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include "DamageComponent.hpp"
#include "HealthComponent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "SizeComponent.hpp"
#include "SizeRectComponent.hpp"
#include "SpeedComponent.hpp"

namespace RType {
    /**
    * @brief Enum to represent different types of component.
    */
    enum class ComponentType {
        Size, /**< Component type for collision. */
        Damage,    /**< Component type for damage. */
        Health,    /**< Component type for health. */
        Player,    /**< Component type for playable _entity. */
        Position,  /**< Component type for position. */
        Speed,      /**< Component type for speed. */
        SizeRect      /**< Component type for size rect. */
    };
}