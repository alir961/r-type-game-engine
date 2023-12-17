/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GraphicBullet.cpp
*/

#include "../../include/entities/GraphicBullet.hpp"
#include "engine/ecs/components/PositionComponent.hpp"
#include <SFML/Graphics.hpp>

using namespace RType;

GraphicBullet::GraphicBullet(Entity &entity) : entity(entity), animationTime(0.0f) {
    // WARN : pour que ça fonctionne ajuste les textures ainsi que le int rect selon le sprite puis les décommente dans main.cpp
    sf::Texture texture;
    texture.loadFromFile("../../assets/r-typesheet42.gif");
    sprite.setTexture(texture);
    currentFrame = sf::IntRect(0, 0, 20, 20);
    sprite.setTextureRect(currentFrame);
}

void GraphicBullet::update(float deltaTime) {
    animationTime += deltaTime;
    auto *position = entity.getComponent<PositionComponent>();
    if (position) {
        sprite.setPosition(position->x, position->y);
    }
}

void GraphicBullet::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
