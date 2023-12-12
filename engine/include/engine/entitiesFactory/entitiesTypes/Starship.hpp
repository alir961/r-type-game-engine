/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../components/CollidingComponent.hpp"
#include "../components/HealthComponent.hpp"
#include "../components/PlayerComponent.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/SpeedComponent.hpp"

/**
 * @brief Class representing a starship entity.
 */
class Starship {
public:
    /**
     * @brief Constructor for Starship.
     * @param isPlayer True if the starship is controlled by a player, false otherwise.
     */
    Starship(bool isPlayer) : healthComponent(100), playerComponent(isPlayer), speedComponent(10), positionComponent({0,0}), collidingComponent(false) {}
private:
    /**
     * @brief Health component of the Starship.
     */
    HealthComponent healthComponent;

    /**
     * @brief Player component of the Starship.
     */
    PlayerComponent playerComponent;

    /**
     * @brief Speed component of the Starship.
     */
    SpeedComponent speedComponent;

    /**
     * @brief Position component of the Starship.
     */
    PositionComponent positionComponent;

    /**
     * @brief Colliding component of the Starship.
     */
    CollidingComponent collidingComponent;
};
