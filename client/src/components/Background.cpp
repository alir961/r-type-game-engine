/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#include "../../include/components/Background.hpp"
#include "../../include/ClientViewport.hpp"

RType::Background::Background(const std::vector<std::string> &imagePaths, const std::vector<float> &speeds) :
        _speeds(speeds) {
    for (const auto &path: imagePaths) {
        const SpriteComponent sprite = _module->createSprite(path);

        _sprites.push_back(sprite);
    }
}

void RType::Background::update(float deltaTime) {
    for (size_t i = 0; i < _sprites.size(); ++i) {
        _sprites[i]->move(-30 * _speeds[i] * deltaTime, 0.0F);
        if (_sprites[i]->getPosition().first + _sprites[i]->getGlobalBounds().width < 0)
            _sprites[i]->setPosition(Vector2f(0.0F, _sprites[i]->getPosition().second));
    }
}

void RType::Background::draw() {
    for (const auto &sprite: _sprites) {
        //const sf::Vector2f newPosition = sprite.getPosition() + sf::Vector2f(WINDOW_WIDTH, 0.0F);
        //sf::Sprite translatedSprite = sprite;
        sprite->draw();
        //translatedSprite.setPosition(newPosition);
        //window.draw(translatedSprite);
    }
}
