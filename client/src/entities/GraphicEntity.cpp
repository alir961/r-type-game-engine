/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GraphicEntity.cpp
*/

#include "../../include/entities/GraphicEntity.hpp"
#include "../../../engine/modules/animation/AnimationModule.hpp"

RType::GraphicEntity::GraphicEntity(EntityPtr &entity, const std::string &entityName) : AGraphicEntity(entityName),
                                                                                        _entity(entity) {
    auto playerSize = _entity->getComponent<SizeComponent>()->getSize();
    const Vector2f &playerPosition = _entity->getComponent<PositionComponent>()->getPosition();

    _playerSprite->setRectangle(RectFloat{0.0F, 0.0F, 33.0F, 15.0F});
    _playerSprite->setScale(Vector2f(playerSize.first, playerSize.second));
    _playerName->setText(_entity->getComponent<PlayerComponent>()->getUsername());
    _playerName->setSize(15);
    _playerName->setPosition(Vector2f(playerPosition.first, playerPosition.second - (playerSize.second + 15)));
    _playerName->setColor(Color::Cyan);
}

void RType::GraphicEntity::update(float deltaTime) {
    auto positionComponent = _entity->getComponent<PositionComponent>();
    auto sizeComponent = _entity->getComponent<SizeComponent>();
    //sf::IntRect rect;

    _animationTime += deltaTime;
    if (_animationTime >= _animationSpeed) {
        //rect = static_cast<sf::IntRect>(animationModule->update(getEntityName()));
        //_playerSprite.setTextureRect(rect);
        _animationTime = 0.0f;
    }
    if (positionComponent != nullptr && sizeComponent != nullptr) {
        auto playerSize = sizeComponent->getSize();
        const Vector2f &playerPosition = positionComponent->getPosition();

        _playerSprite->setPosition(positionComponent->getPosition());
        _playerName->setPosition(Vector2f(playerPosition.first, playerPosition.second - (playerSize.second + 15)));
    }
}

void RType::GraphicEntity::draw() {
    _playerSprite->draw();
    if (_entity->getComponent<PlayerComponent>()->getIsPlayer())
        _playerName->draw();
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
