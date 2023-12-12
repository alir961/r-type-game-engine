/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../components/CollisionComponent.hpp"
#include "../components/HealthComponent.hpp"
#include "../components/PlayerComponent.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/SpeedComponent.hpp"

/**
 * @brief Class representing a monster entity.
 */
class Monster {
public:
    /**
     * @brief Constructor for Monster.
     */
    Monster() : healthComponent(200), speedComponent(10), positionComponent({0,0}), collidingComponent(true) {}
private:
    /**
     * @brief Health component of the Monster.
     */
    HealthComponent healthComponent;

    /**
     * @brief Speed component of the Monster.
     */
    SpeedComponent speedComponent;

    /**
     * @brief Position component of the Monster.
     */
    PositionComponent positionComponent;

    /**
     * @brief Colliding component of the Monster.
     */
    CollisionComponent collidingComponent;
};
