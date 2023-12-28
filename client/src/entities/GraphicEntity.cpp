/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GraphicEntity.cpp
*/

#include "../../include/entities/GraphicEntity.hpp"
#include "../ResourceManager.hpp"

extern ResourceManager resourceManager;

RType::GraphicEntity::GraphicEntity(std::shared_ptr<Entity> &entity, const std::string &path)
    : entity(entity), animationTime(0.0f), animationSpeed(0.1f) {
    resourceManager.loadTexture("entityTexture", path);
    sprite.setTexture(resourceManager.getTexture("entityTexture"));
    currentFrame = sf::IntRect(0, 0, 50, 25);
    sprite.setTextureRect(currentFrame);
}

void RType::GraphicEntity::update(float deltaTime) {
    animationTime += deltaTime;
    if (animationTime >= animationSpeed) {
        currentFrame.left += 32;
        if (currentFrame.left >= sprite.getTexture()->getSize().x) {
            currentFrame.left = 0;
        }
        sprite.setTextureRect(currentFrame);
        animationTime = 0.0f;
    }

    auto position = entity->getComponent<PositionComponent>();
    if (position) {
        sprite.setPosition(static_cast<float>(position->getPosition().first),
                           static_cast<float>(position->getPosition().second));
    }
}

void RType::GraphicEntity::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
