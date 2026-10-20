/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GraphicEntity.cpp
*/

#include <utility>

#include "../../include/entities/GraphicEntity.hpp"
#include "engine/tools/Split.hpp"
#include <algorithm>

RType::GraphicEntity::GraphicEntity(EntityPtr entity, const std::string &path, const std::string &entityName)
        : AGraphicEntity(entityName),
          _entity(std::move(entity)) {
    const auto &[sizeX, sizeY] = _entity->getComponent<SizeComponent>()->getSize();

    if (_entity->hasHealthComponent()) {
        _initialHealth = _entity->getComponent<HealthComponent>()->getHealth();
        _lastHealth = _initialHealth;
    }
    _entitySprite = _module->createSprite(path);
    _entitySprite->setScale(Vector2f(sizeX, sizeY));
    _entitySprite->setPosition(_entity->getComponent<PositionComponent>()->getPosition());
    refreshAnimation();
    _healthBackground->setBackgroundColor(Color::RGB{10, 10, 20, 200});
    _healthBackground->setOutlineColor(Color::RGB{0, 0, 0, 220});
    _healthBackground->setOutlineThickness(1.0F);
    _hitbox->setBackgroundColor(Color::Transparent);
    _hitbox->setOutlineColor(Color::RGB{255, 60, 200, 255});
    _hitbox->setOutlineThickness(1.0F);
}

void RType::GraphicEntity::refreshAnimation() {
    const std::string name = Split::split(_entity->getEntityName(), " \n")[0];

    if (_animation != nullptr && name == _animationName)
        return;
    _animationName = name;
    _animation = _animationModule->createAnimation(name);
    _animationTime = 0.0F;
    _entitySprite->setRectangle(_animation->getCurrentFrame());
    _entityNameText.setColor(Theme::playerColor(name));
}

void RType::GraphicEntity::update(float deltaTime) {
    auto positionComponent = _entity->getComponent<PositionComponent>();
    auto sizeComponent = _entity->getComponent<SizeComponent>();

    refreshAnimation();
    _animationTime += deltaTime;
    while (_animationTime >= _animation->getFrameDuration()) {
        _entitySprite->setRectangle(_animation->update());
        _animationTime -= _animation->getFrameDuration();
    }
    bool wasHit = false;
    if (_entity->hasHealthComponent()) {
        const int health = _entity->getComponent<HealthComponent>()->getHealth();

        wasHit = health < _lastHealth;
        if (wasHit)
            _hitFlashTime = 0.15F;
        _lastHealth = health;
    }
    _hitFlashTime = std::max(0.0F, _hitFlashTime - deltaTime);
    _entitySprite->setColor(_hitFlashTime > 0.0F ? Color::RGB{255, 110, 110, 255} : Color::White);
    if (positionComponent != nullptr && sizeComponent != nullptr) {
        const auto &[sizeX, sizeY] = sizeComponent->getSize();
        const auto &[posX, posY] = positionComponent->getPosition();
        const float width = sizeX * _entity->getComponent<SizeRectComponent>()->getSize().first;

        _entitySprite->setScale(Vector2f(sizeX, sizeY));
        _entitySprite->setPosition(positionComponent->getPosition());
        _entityNameText.setPosition(posX + width / 2.0F, posY - 44.0F);
    }
    emitParticles(wasHit);
}

void RType::GraphicEntity::emitParticles(bool wasHit) {
    const auto &[posX, posY] = _entity->getComponent<PositionComponent>()->getPosition();
    const auto &[sizeX, sizeY] = _entity->getComponent<SizeComponent>()->getSize();
    const auto &[rectX, rectY] = _entity->getComponent<SizeRectComponent>()->getSize();
    const float height = sizeY * rectY;

    if (wasHit)
        Particles::sparks(getCenter(), Color::RGB{255, 230, 160, 255}, 12);
    if (_animationName.ends_with("Player") && _animationName != "bulletPlayer") {
        // Exhaust leaves the back of the ship, to the left.
        Color::RGB color = Theme::playerColor(_animationName);
        color.a = 230;
        Particles::trail({posX + 4.0F, posY + height / 2.0F}, color, Particles::PI);
    } else if (_animationName == "starship") {
        Particles::trail({posX + sizeX * rectX - 4.0F, posY + height / 2.0F}, Color::RGB{120, 200, 255, 220}, 0.0F);
    }
}

void RType::GraphicEntity::draw() {
    const auto playerComponent = _entity->getComponent<PlayerComponent>();
    const bool isPlayer = playerComponent != nullptr && playerComponent->getIsPlayer();

    _entitySprite->draw();
    if (showHitboxes) {
        const auto &[posX, posY] = _entity->getComponent<PositionComponent>()->getPosition();
        const auto &[sizeX, sizeY] = _entity->getComponent<SizeComponent>()->getSize();
        const auto &[rectX, rectY] = _entity->getComponent<SizeRectComponent>()->getSize();

        _hitbox->setPosition(Vector2f(posX, posY));
        _hitbox->setSize(Vector2f(sizeX * rectX, sizeY * rectY));
        _hitbox->draw();
    }
    // Enemies only show their health once hit, players always do.
    if (_entity->hasHealthComponent() && (isPlayer || _lastHealth < _initialHealth))
        drawHealthBar();
    if (isPlayer) {
        _entityNameText.setText(playerComponent->getUsername());
        _entityNameText.draw();
    }
}

RType::Vector2f RType::GraphicEntity::getCenter() const {
    const auto &[posX, posY] = _entity->getComponent<PositionComponent>()->getPosition();
    const auto &[sizeX, sizeY] = _entity->getComponent<SizeComponent>()->getSize();
    const auto &[rectX, rectY] = _entity->getComponent<SizeRectComponent>()->getSize();

    return {posX + sizeX * rectX / 2.0F, posY + sizeY * rectY / 2.0F};
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

void RType::GraphicEntity::drawHealthBar() {
    const int currentHealth = _entity->getComponent<HealthComponent>()->getHealth();
    const float healthRatio = std::clamp(static_cast<float>(currentHealth) / static_cast<float>(std::max(1, _initialHealth)), 0.0F, 1.0F);
    const auto &[posX, posY] = _entity->getComponent<PositionComponent>()->getPosition();
    const auto &[sizeX, sizeY] = _entity->getComponent<SizeComponent>()->getSize();
    const auto &[sizeRectX, sizeRectY] = _entity->getComponent<SizeRectComponent>()->getSize();
    const float barWidth = sizeX * sizeRectX;
    const float barHeight = 6.0F;
    const float barPosY = posY - barHeight - 10.0F;

    _healthBackground->setPosition(Vector2f(posX, barPosY));
    _healthBackground->setSize(Vector2f(barWidth, barHeight));
    _healthFill->setPosition(Vector2f(posX, barPosY));
    _healthFill->setSize(Vector2f(barWidth * healthRatio, barHeight));
    _healthFill->setBackgroundColor(Theme::healthColor(healthRatio));
    _healthBackground->draw();
    _healthFill->draw();
}
