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
#include <memory>

class EntityFactory {
public:
    static std::shared_ptr<ADamageable> createStarship() {
        return std::make_shared<Starship>();
    }

    static std::shared_ptr<AWeapon> createBullet() {
        return std::make_shared<Bullet>();
    }
};