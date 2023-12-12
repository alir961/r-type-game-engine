/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../components/CollisionComponent.hpp"
#include "../components/DamageComponent.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/SpeedComponent.hpp"

/**
 * @brief Class representing a bullet entity.
 */
class Bullet {
public:
    /**
     * @brief Constructor for Bullet.
     */
    Bullet() : damageComponent(25), speedComponent(20), positionComponent({0,0}), collisionComponent(true) {}
private:
    /**
     * @brief Damage component of the Bullet.
     */
    DamageComponent damageComponent;

    /**
     * @brief Speed component of the Bullet.
     */
    SpeedComponent speedComponent;

    /**
     * @brief Position component of the Bullet.
     */
    PositionComponent positionComponent;

    /**
     * @brief Colliding component of the Bullet.
     */
    CollisionComponent collisionComponent;
};
