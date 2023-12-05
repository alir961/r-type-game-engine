/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "IEntity.hpp"
#include <memory>

class EntityFactory {
public:
    static std::shared_ptr<Entity> createStarship() {
        return std::make_shared<Starship>();
    }

    static std::shared_ptr<Entity> createBullet() {
        return std::make_shared<Bullet>();
    }
};