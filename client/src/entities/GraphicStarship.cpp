/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GraphicStarship.cpp
*/

#include "../../include/entities/GraphicStarship.hpp"
#include "engine/ecs/components/PositionComponent.hpp"
#include <SFML/Graphics.hpp>

using namespace RType;

GraphicStarship::GraphicStarship(Entity &entity) : entity(entity), animationTime(0.0f) {
    sf::Texture texture;
    texture.loadFromFile("../../assets/r-typesheet42.gif");
    sprite.setTexture(texture);
    currentFrame = sf::IntRect(starship_height + starship_number, 0, 33.2, 17.2);
    sprite.setTextureRect(currentFrame);
}

void GraphicStarship::update(float deltaTime) {
    animationTime += deltaTime;
    if (animationTime >= 0.1f) {
        currentFrame.left += 32;
        if (currentFrame.left >= sprite.getTexture()->getSize().x) {
            currentFrame.left = 0;
        }
        sprite.setTextureRect(currentFrame);
        animationTime = 0.0f;
    }
}

void GraphicStarship::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
