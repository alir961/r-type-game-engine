/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GraphicEntity.cpp
*/

#include "../../include/entities/GraphicEntity.hpp"
#include <SFML/Graphics.hpp>

GraphicEntity::GraphicEntity(std::shared_ptr<Entity> &entity) : entity(entity), animationTime(0.0f) {
    sf::Texture texture;
    texture.loadFromFile("../../assets/r-typesheet42.gif");
    sprite.setTexture(texture);
    currentFrame = sf::IntRect(100 + 1, 0, 50, 25); // NEED refact when we use it
    sprite.setTextureRect(currentFrame);
}

void GraphicEntity::update(float deltaTime) {
    animationTime += deltaTime;
    if (animationTime >= 0.1f) {
        currentFrame.left += 32;
        if (currentFrame.left >= sprite.getTexture()->getSize().x) {
            currentFrame.left = 0;
        }
        sprite.setTextureRect(currentFrame);
        animationTime = 0.0f;
    }

    std::shared_ptr position = entity->getComponent<PositionComponent>();
    if (position) {
        sprite.setPosition(position->getPositions().first, position->getPositions().second);
    }
}

void GraphicEntity::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
