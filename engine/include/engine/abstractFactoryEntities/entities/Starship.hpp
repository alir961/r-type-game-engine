/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <map>

class Starship : public Entity {
public:
    Starship() : health(100), speed(10) {

    }
    void setPositions(std::map<int, int> pos) {
        position = pos;
    }
};
