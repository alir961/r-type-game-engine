/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <map>

class AEntity {
public:
    void setPositions(std::map<int, int> position) {
        _position = position;
    }
    void setSpeed(int speed) {
        _speed = speed;
    }
    void getPositions() {
        return _position;
    }
    void getSpeed() {
        return _speed;
    }
private:
    int _speed;
    std::map<int, int> _position;
};
