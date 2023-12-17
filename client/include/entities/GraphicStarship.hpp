/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GraphicStarship.hpp
*/

#pragma once
#include "IGraphicEntity.hpp"
#include "engine/ecs/Entity.hpp"
#include <SFML/Graphics.hpp>

namespace RType {

    class GraphicStarship : public IGraphicEntity {
    public:
        explicit GraphicStarship(engine::ecs::Entity &entity);

        void update(float deltaTime) override;
        void draw(sf::RenderWindow &window) override;

    private:
        engine::ecs::Entity &entity;
        sf::Sprite sprite;
        sf::IntRect currentFrame;
        float animationTime;
        float animationSpeed;
    };
}// namespace RType
