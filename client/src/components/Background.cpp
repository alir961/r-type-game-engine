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
        const SpriteComponent translatedSprite = _module->createSprite(path);
        const float scaleX = static_cast<float>(WINDOW_WIDTH) / sprite->getGlobalBounds().width;
        const float scaleY = static_cast<float>(WINDOW_HEIGHT) / sprite->getGlobalBounds().height;

        sprite->setScale(Vector2f(scaleX, scaleY));
        translatedSprite->setScale(Vector2f(scaleX, scaleY));
        translatedSprite->setPosition(Vector2f(WINDOW_WIDTH, 0.0F));
        _sprites.push_back(sprite);
        _translatedSprites.push_back(translatedSprite);
    }
}

void RType::Background::update(float deltaTime) {
    for (size_t i = 0; i < _sprites.size(); ++i) {
        const SpriteComponent sprite = _sprites[i];

        sprite->move(-30 * _speeds[i] * deltaTime, 0.0F);
        if (sprite->getPosition().first + sprite->getGlobalBounds().width <= 0)
            _sprites[i]->setPosition(Vector2f(0.0, 0.0));
        _translatedSprites[i]->setPosition(Vector2f(sprite->getPosition().first + sprite->getGlobalBounds().width, 0.0F));
    }
}

void RType::Background::draw() {
    for (size_t i = 0; i < _sprites.size(); ++i) {
        _sprites[i]->draw();
        _translatedSprites[i]->draw();
    }
}
