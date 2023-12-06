/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <map>
#include "../IEntity.hpp"

class Bullet : public IEntity {
public:
    Bullet() : damage(25), speed(20) {

    }
    void setPositions(std::map<int, int> pos) {
        position = pos;
    }
};
