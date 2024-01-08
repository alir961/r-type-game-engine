/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GraphicEntity.cpp
*/

#include "../../include/entities/GraphicEntity.hpp"

RType::GraphicEntity::GraphicEntity(EntityPtr &entity, const std::string& path, const std::string& entityName, AnimationModule* animationModule)
    : _entity(entity), _animationTime(0.0f), _animationSpeed(0.1f), AGraphicEntity(entityName), _animationModule(animationModule) {
    _resourceManager.loadTexture(entityName, path);
    _sprite.setTexture(_resourceManager.getTexture(entityName));
    _animationModule->initAnimation(_entity, path);
}

void RType::GraphicEntity::update(float deltaTime) {
    _animationTime += deltaTime;
    if (_animationTime >= _animationSpeed) {
        _animationModule->updateAnimation(_entity, deltaTime);
        _currentFrame = _animationModule->getCurrentFrame(_entity);
        _sprite.setTextureRect(_currentFrame);
        _animationTime = 0.0f;
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

EntityPtr RType::GraphicEntity::getEntity() {
    return _entity;
}

sf::Sprite RType::GraphicEntity::getSprite() {
    return _sprite;
}
