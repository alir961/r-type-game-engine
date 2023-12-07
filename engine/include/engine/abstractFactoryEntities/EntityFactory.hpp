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

class EntityFactory {
public:
    static std::shared_ptr<ADamageable> createPlayerStarship() {
        return std::make_shared<Starship>(true);
    }

    static std::shared_ptr<ADamageable> createEnemyStarship() {
        return std::make_shared<Starship>(false);
    }

    static std::shared_ptr<Monster> createMonster() {
        return std::make_shared<Monster>();
    }

    static std::shared_ptr<AWeapon> createBullet() {
        return std::make_shared<Bullet>();
    }
};