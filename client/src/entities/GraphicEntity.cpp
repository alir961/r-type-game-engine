/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GraphicEntity.cpp
*/

#include "../../include/entities/GraphicEntity.hpp"
#include "../../../engine/modules/animation/AnimationModule.hpp"

RType::GraphicEntity::GraphicEntity(EntityPtr &entity, const std::string &path, const std::string &entityName) : AGraphicEntity(entityName),
                                                                                        _entity(entity) {
    const auto &size = _entity->getComponent<SizeComponent>()->getSize();
    const auto &position = _entity->getComponent<PositionComponent>()->getPosition();
    const auto &rect = _entity->getComponent<SizeRectComponent>()->getSize();

    _entitySprite = _module->createSprite(path);
    if (entityName.starts_with("bullet"))
        _entitySprite->setRectangle(RectFloat{101.0F, 118.0F, rect.first, rect.second});
    else _entitySprite->setRectangle(RectFloat{0.0F, 0.0F, 33.0F, 15.0F});
    _entitySprite->setScale(Vector2f(size.first, size.second));
    _entityNameText->setText(_entity->getComponent<PlayerComponent>()->getUsername());
    _entityNameText->setSize(15);
    _entityNameText->setPosition(Vector2f(position.first, position.second - (size.second + 15)));
    _entityNameText->setColor(Color::Cyan);
}

void RType::GraphicEntity::update(float deltaTime) {
    auto positionComponent = _entity->getComponent<PositionComponent>();
    auto sizeComponent = _entity->getComponent<SizeComponent>();
    //sf::IntRect rect;

    _animationTime += deltaTime;
    if (_animationTime >= _animationSpeed) {
        //rect = static_cast<sf::IntRect>(animationModule->update(getEntityName()));
        //_entitySprite.setTextureRect(rect);
        _animationTime = 0.0f;
    }
    if (positionComponent != nullptr && sizeComponent != nullptr) {
        const auto &size = sizeComponent->getSize();
        const auto &position = positionComponent->getPosition();

        _entitySprite->setPosition(positionComponent->getPosition());
        _entityNameText->setPosition(Vector2f(position.first, position.second - (size.second + 15)));
    }
}

void RType::GraphicEntity::draw() {
    _entitySprite->draw();
    if (_entity->getComponent<PlayerComponent>()->getIsPlayer())
        _entityNameText->draw();
}

void RType::GraphicEntity::moveLeft() {
    auto speed = static_cast<float>(_entity->getComponent<SpeedComponent>()->getSpeed());
    const auto &[x, y] = _entity->getComponent<PositionComponent>()->getPosition();

    getSprite()->move(-speed, 0.0F);
    _entity->getComponent<PositionComponent>()->setPositions(Vector2f(x - speed, y));
}

void RType::GraphicEntity::moveRight() {
    auto speed = static_cast<float>(_entity->getComponent<SpeedComponent>()->getSpeed());
    const auto &[x, y] = _entity->getComponent<PositionComponent>()->getPosition();

    getSprite()->move(speed, 0.0F);
    _entity->getComponent<PositionComponent>()->setPositions(Vector2f(x + speed, y));
}

void RType::GraphicEntity::moveUp() {
    auto speed = static_cast<float>(_entity->getComponent<SpeedComponent>()->getSpeed());
    const auto &[x, y] = _entity->getComponent<PositionComponent>()->getPosition();

    getSprite()->move(0.0F, -speed);
    _entity->getComponent<PositionComponent>()->setPositions(Vector2f(x, y - speed));
}

void RType::GraphicEntity::moveDown() {
    auto speed = static_cast<float>(_entity->getComponent<SpeedComponent>()->getSpeed());
    const auto &[x, y] = _entity->getComponent<PositionComponent>()->getPosition();

    getSprite()->move(0.0F, speed);
    _entity->getComponent<PositionComponent>()->setPositions(Vector2f(x, y + speed));
}
