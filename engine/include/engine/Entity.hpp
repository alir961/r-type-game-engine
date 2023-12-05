/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <map>

class Entity {
public:
    virtual void update() = 0;
    virtual void render() = 0;
};

class Starship : public Entity {
public:
    Starship() : health(100), speed(10) {

    }

    void update() override {
    }

    void render() override {
    }
private:
    int health;
    int speed;
    std::map<int, int> position;
};

class Bullet : public Entity {
public:
    bullet() : damage(25), speed(20) {

    }

    void update() override {
    }

    void render() override {
    }
private:
    int damage;
    int speed;
    std::map<int, int> position;
};