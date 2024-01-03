/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#include "../../include/components/Background.hpp"

RType::Background::Background(sf::RenderWindow &window, const std::vector<std::string> &imagePaths, const std::vector<float> &speeds) {
    for (const auto& path : imagePaths) {
        sf::Texture texture;
        texture.loadFromFile(path);
        textures.push_back(texture);
    }
    for (size_t i = 0; i < textures.size(); ++i) {
        sf::Sprite sprite(textures[i]);

        float scaleX = window.getSize().x / sprite.getGlobalBounds().width;
        float scaleY = window.getSize().y / sprite.getGlobalBounds().height;

        sprite.setScale(scaleX, scaleY);

        sprites.push_back(sprite);
    }
    this->speeds = speeds;
}

void RType::Background::update(float deltaTime) {
    for (size_t i = 0; i < sprites.size(); ++i) {
        sprites[i].move(-30 * speeds[i] * deltaTime, 0.0f);
        if (sprites[i].getPosition().x + sprites[i].getGlobalBounds().width < 0) {
            sprites[i].setPosition(0.0f, sprites[i].getPosition().y);
        }
    }
}

void RType::Background::draw(sf::RenderWindow &window) {
    for (const auto& sprite : sprites) {
        window.draw(sprite);
        sf::Vector2f newPosition = sprite.getPosition() + sf::Vector2f(window.getSize().x, 0.0f);
        sf::Sprite translatedSprite = sprite;
        translatedSprite.setPosition(newPosition);
        window.draw(translatedSprite);
    }

}
