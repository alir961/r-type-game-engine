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
    void setColliding(bool isColliding) {
        _isColliding = isColliding;
    }
    std::map<int, int> getPositions() {
        return _position;
    }
    int getSpeed() {
        return _speed;
    }
    bool getColliding() {
        return _isColliding;
    }
protected:
    int _speed;
    std::map<int, int> _position;
    bool _isColliding;
};
