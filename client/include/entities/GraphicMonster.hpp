/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GraphicMonster.hpp
*/

#pragma once
#include "IGraphicEntity.hpp"
#include "engine/ecs/Entity.hpp"
#include "engine/ecs/component/PositionComponent.hpp"
#include <SFML/Graphics.hpp>

class GraphicMonster : public IGraphicEntity {
public:
    explicit GraphicMonster(std::shared_ptr<Entity> &entity);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow &window) override;

private:
    std::shared_ptr<Entity> &entity;
    sf::Sprite sprite;
    sf::IntRect currentFrame;
    float animationTime;
    float animationSpeed;
};
