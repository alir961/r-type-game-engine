/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GraphicStarship.cpp
*/

#include "../../include/entities/GraphicStarship.hpp"
#include <SFML/Graphics.hpp>

GraphicStarship::GraphicStarship(std::shared_ptr<Entity> &entity) : entity(entity), animationTime(0.0f) {
    sf::Texture texture;
    texture.loadFromFile("../../assets/r-typesheet42.gif");
    sprite.setTexture(texture);
    currentFrame = sf::IntRect(100 + 1, 0, 50, 25); // NEED refact when we use it
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
