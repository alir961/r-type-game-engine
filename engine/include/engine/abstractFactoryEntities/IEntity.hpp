/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <map>

class IEntity {
public:
    virtual void setPositions() = 0;
private:
    int health;
    int speed;
    int damage;
    std::map<int, int> position;
};
