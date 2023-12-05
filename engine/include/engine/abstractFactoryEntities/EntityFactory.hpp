/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <memory>
#include "IEntity.hpp"
#include "entities/Starship.hpp"
#include "entities/Bullet.hpp"

class EntityFactory {
public:
    static std::shared_ptr<IEntity> createStarship() {
        return std::make_shared<Starship>();
    }

    static std::shared_ptr<IEntity> createBullet() {
        return std::make_shared<Bullet>();
    }
};