/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GraphicBullet.cpp
*/

#include "../../include/entities/GraphicBullet.hpp"
#include <SFML/Graphics.hpp>

GraphicBullet::GraphicBullet(std::shared_ptr<Entity> &entity) : entity(entity), animationTime(0.0f) {
    // WARN : pour que ça fonctionne ajuste les textures ainsi que le int rect selon le sprite puis les décommente dans main.cpp
    sf::Texture texture;
    texture.loadFromFile("../../assets/r-typesheet42.gif");
    sprite.setTexture(texture);
    currentFrame = sf::IntRect(0, 0, 20, 20);
    sprite.setTextureRect(currentFrame);
}

void GraphicBullet::update(float deltaTime) {
    animationTime += deltaTime;
    std::shared_ptr position = entity->getComponent<PositionComponent>();
    if (position) {
        sprite.setPosition(position->getPositions().first, position->getPositions().second);
    }
}

void GraphicBullet::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
