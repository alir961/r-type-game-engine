/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GraphicEntity.cpp
*/

#include "../../include/entities/GraphicEntity.hpp"
#include "../../../engine/modules/animation/AnimationModule.hpp"

RType::GraphicEntity::GraphicEntity(EntityPtr &entity, const std::string& path, const std::string& entityName)
    : _entity(entity), AGraphicEntity(entityName) {
      _resourceManager.loadTexture(entityName, path);
      auto entitySize = _entity->getComponent<SizeComponent>()->getSize();
      _sprite.setScale(entitySize.first, entitySize.second);
}

void RType::GraphicEntity::update(float deltaTime, IAnimationModule *animationModule) {
    auto position = _entity->getComponent<PositionComponent>();
    sf::IntRect rect;

    _animationTime += deltaTime;
    if (_animationTime >= _animationSpeed) {
        rect = static_cast<sf::IntRect>(animationModule->update(getEntityName()));
        _sprite.setTextureRect(rect);
        _animationTime = 0.0f;

    }
    if (position) {
        _sprite.setPosition(float(position->getPositions().first),
                            float(position->getPositions().second));
    }
}

void RType::GraphicEntity::draw(sf::RenderWindow &window, IGraphicalModule *graphicalModule) {
    graphicalModule->drawSprite(window, _sprite);
}

void RType::GraphicEntity::loadSprite(RType::IAnimationModule *animationModule) {
    auto entitySize = _entity->getComponent<SizeComponent>()->getSize();
    auto rect = static_cast<sf::IntRect>(animationModule->update(getEntityName()));

    _sprite.setTexture(_resourceManager.getTexture(getEntityName()));
    _sprite.setTextureRect(rect);
    _sprite.setScale(entitySize.first, entitySize.second);
}
