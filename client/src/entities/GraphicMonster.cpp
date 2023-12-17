/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GraphicMonster.cpp
*/

#include "../../include/entities/GraphicMonster.hpp"
#include "engine/ecs/components/PositionComponent.hpp"
#include <SFML/Graphics.hpp>

using namespace RType;

GraphicMonster::GraphicMonster(engine::ecs::Entity &entity) : entity(entity), animationTime(0.0f) {
    // WARN : pour que ça fonctionne ajuste les textures ainsi que le int rect selon le sprite puis les décommente dans main.cpp
    sf::Texture texture;
    texture.loadFromFile("../../assets/r-typesheet42.gif");
    sprite.setTexture(texture);
    currentFrame = sf::IntRect(0, 0, 32, 32);
    sprite.setTextureRect(currentFrame);
}

void GraphicMonster::update(float deltaTime) {
    animationTime += deltaTime;
    if (animationTime >= 0.1f) {
        currentFrame.left += 32;
        if (currentFrame.left >= sprite.getTexture()->getSize().x) {
            currentFrame.left = 0;
        }
        sprite.setTextureRect(currentFrame);
        animationTime = 0.0f;
    }

    auto *position = entity.getComponent<PositionComponent>();
    if (position) {
        sprite.setPosition(position->x, position->y);
    }
}

void GraphicMonster::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
