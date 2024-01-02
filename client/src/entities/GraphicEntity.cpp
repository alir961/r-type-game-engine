/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GraphicEntity.cpp
*/

#include "../../include/entities/GraphicEntity.hpp"

RType::GraphicEntity::GraphicEntity(std::shared_ptr<Entity> &entity, const std::string path, const std::string entityName)
    : _entity(entity), _animationTime(0.0f), _animationSpeed(0.1f), AGraphicEntity(entityName) {
    _resourceManager.loadTexture(entityName, path);
    _sprite.setTexture(_resourceManager.getTexture(entityName));
    _currentFrame = sf::IntRect(0, 0, 33, 15);
    _sprite.setTextureRect(_currentFrame);
    _sprite.setScale(2.0f, 2.0f);
}

void RType::GraphicEntity::update(float deltaTime) {
    _animationTime += deltaTime;
    if (_animationTime >= _animationSpeed) {
        if (_currentFrame.left >= _sprite.getTexture()->getSize().x - 33) {
            _currentFrame.left = 0;
        }
        _sprite.setTextureRect(_currentFrame);
        _animationTime = 0.0f;
        _currentFrame.left += 33;

    }

    auto position = _entity->getComponent<PositionComponent>();
    if (position) {
        _sprite.setPosition(float(position->getPositions().first),
                           float(position->getPositions().second));
    }
}

void RType::GraphicEntity::draw(sf::RenderWindow &window, IGraphicalModule *graphicalModule) {
    graphicalModule->drawSprite(window, _sprite);
}
