/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GraphicStarship.hpp
*/

#pragma once
#include "AGraphicEntity.hpp"
#include <SFML/Graphics.hpp>

class GraphicStarship : public AGraphicEntity {
public:
    explicit GraphicStarship(std::shared_ptr<Entity> &entity);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow &window) override;

    std::shared_ptr<Entity> getEntity() override {
        return entity;
    }

    sf::Sprite getSprite() override {
        return sprite;
    }

private:
    std::shared_ptr<Entity> &entity;
    sf::Sprite sprite;
    sf::IntRect currentFrame;
    float animationTime;
    float animationSpeed;
};
