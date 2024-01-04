/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#include "../../include/components/Background.hpp"

RType::Background::Background(const sf::RenderWindow &window, const std::vector<std::string> &imagePaths,
                              const std::vector<float> &speeds) : _speeds(speeds) {
    for (const auto &path: imagePaths) {
        sf::Texture texture;
        texture.loadFromFile(path);
        _textures.push_back(texture);
    }
    for (const auto &texture: _textures) {
        sf::Sprite sprite(texture);
        const float scaleX = static_cast<float>(window.getSize().x) / sprite.getGlobalBounds().width;
        const float scaleY = static_cast<float>(window.getSize().y) / sprite.getGlobalBounds().height;

        sprite.setScale(scaleX, scaleY);
        _sprites.push_back(sprite);
    }
}

void RType::Background::update(float deltaTime) {
    for (size_t i = 0; i < _sprites.size(); ++i) {
        _sprites[i].move(-30 * _speeds[i] * deltaTime, 0.0F);
        if (_sprites[i].getPosition().x + _sprites[i].getGlobalBounds().width < 0)
            _sprites[i].setPosition(0.0F, _sprites[i].getPosition().y);
    }
}

void RType::Background::draw(sf::RenderWindow &window) {
    for (const auto &sprite: _sprites) {
        const sf::Vector2f newPosition = sprite.getPosition() + sf::Vector2f(window.getSize().x, 0.0F);
        sf::Sprite translatedSprite = sprite;

        window.draw(sprite);
        translatedSprite.setPosition(newPosition);
        window.draw(translatedSprite);
    }

}
