/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <Entity.hpp>

class EntityFactory {
public:
    static Entity* createStarship() {
        return new Starship();
    }

    static Entity* createBullet() {
        return new Bullet();
    }
};