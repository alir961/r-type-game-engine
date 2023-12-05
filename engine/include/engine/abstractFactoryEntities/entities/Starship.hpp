/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <map>
#include "../IEntity.hpp"

class Starship : public IEntity {
public:
    Starship() : health(100), speed(10) {

    }
    void setPositions(std::map<int, int> pos) {
        position = pos;
    }
};
