/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "./entititiesTypes/ADamageable.hpp"
#include "./entititiesTypes/AWeapon.hpp"
#include "./entititiesTypes/entities/Bullet.hpp"
#include "./entititiesTypes/entities/Starship.hpp"
#include "./entititiesTypes/entities/Monster.hpp"
#include <memory>

/**
 * @brief Abstract Factory for creating game entities.
 */
class EntityFactory {
public:
    /**
     * @brief Create a player-controlled starship.
     * @return A shared pointer to the created ADamageable object.
     */
    static std::shared_ptr<ADamageable> createPlayerStarship() {
        return std::make_shared<Starship>(true);
    }

    /**
     * @brief Create an enemy-controlled starship.
     * @return A shared pointer to the created ADamageable object.
     */
    static std::shared_ptr<ADamageable> createEnemyStarship() {
        return std::make_shared<Starship>(false);
    }

    static std::shared_ptr<Monster> createMonster() {
        return std::make_shared<Monster>();
    }

    /**
     * @brief Create a bullet entity.
     * @return A shared pointer to the created AWeapon object.
     */
    static std::shared_ptr<AWeapon> createBullet() {
        return std::make_shared<Bullet>();
    }
};
