/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "./entitiesTypes/Bullet.hpp"
#include "./entitiesTypes/Monster.hpp"
#include "./entitiesTypes/Starship.hpp"
#include <memory>

class Starship;
class Monster;
class Bullet;

/**
 * @brief Factory for creating game entities.
 */
class EntityFactory {
public:
    /**
     * @brief Create a player-controlled starship.
     * @return A shared pointer to the created Starship object.
     */
    static std::shared_ptr<Starship> createPlayerStarship() {
        return std::make_shared<Starship>(true);
    }

    /**
     * @brief Create an enemy-controlled starship.
     * @return A shared pointer to the created Starship object.
     */
    static std::shared_ptr<Starship> createEnemyStarship() {
        return std::make_shared<Starship>(false);
    }

    /**
     * @brief Create an enemy-controlled monster.
     * @return A shared pointer to the created Monster object.
     */
    static std::shared_ptr<Monster> createMonster() {
        return std::make_shared<Monster>();
    }

    /**
     * @brief Create a bullet entity.
     * @return A shared pointer to the created Bullet object.
     */
    static std::shared_ptr<Bullet> createBullet() {
        return std::make_shared<Bullet>();
    }
};
