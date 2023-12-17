/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GraphicMonster.hpp
*/

#pragma once
#include "IGraphicEntity.hpp"
#include "engine/ecs/Entity.hpp"
#include <SFML/Graphics.hpp>

namespace RType {

    class GraphicMonster : public IGraphicEntity {
    public:
        explicit GraphicMonster(Entity &entity);

        void update(float deltaTime) override;
        void draw(sf::RenderWindow &window) override;

    private:
        Entity &entity;
        sf::Sprite sprite;
        sf::IntRect currentFrame;
        float animationTime;
        float animationSpeed;
    };
}// namespace RType
