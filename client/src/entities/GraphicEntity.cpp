/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GraphicEntity.cpp
*/

#include "../../include/entities/GraphicEntity.hpp"
#include "../../../engine/modules/animation/AnimationModule.hpp"

RType::GraphicEntity::GraphicEntity(EntityPtr &entity, const std::string& path, const std::string& entityName)
    : _entity(entity), _animationTime(0.0f), _animationSpeed(0.1f), AGraphicEntity(entityName) {
    _resourceManager.loadTexture(entityName, path);
    _sprite.setTexture(_resourceManager.getTexture(entityName));
}

void RType::GraphicEntity::update(float deltaTime) {
    _animationTime += deltaTime;
    if (_animationTime >= _animationSpeed) {
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