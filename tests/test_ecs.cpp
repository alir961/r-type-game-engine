#include <gtest/gtest.h>

#include "ecs/EntityManager.hpp"

using namespace RType;

namespace {

    // Builds an entity with everything movement and collisions need.
    EntityPtr makeShip(EntityManager &manager, const std::string &name, int x, int y, int health = 100) {
        EntityPtr entity = manager.createEntity();
        entity->setEntityName(name);
        entity->addComponent<PositionComponent>(std::make_pair(x, y));
        entity->addComponent<SizeComponent>(10.0F, 10.0F);
        entity->addComponent<SizeRectComponent>(1.0F, 1.0F);
        entity->addComponent<SpeedComponent>(5);
        entity->addComponent<HealthComponent>(health);
        return entity;
    }

    std::pair<int, int> position(const EntityPtr &entity) {
        return entity->getComponent<PositionComponent>()->getPositions();
    }

    constexpr float WIDTH = 800.0F;
    constexpr float HEIGHT = 600.0F;

}

TEST(Entity, AddGetRemoveComponent) {
    Entity entity;
    EXPECT_FALSE(entity.hasComponents());
    ASSERT_NE(entity.addComponent<HealthComponent>(3), nullptr);
    EXPECT_EQ(entity.getComponent<HealthComponent>()->getHealth(), 3);
    EXPECT_EQ(entity.getComponent<SpeedComponent>(), nullptr);

    entity.removeComponent<HealthComponent>();
    EXPECT_EQ(entity.getComponent<HealthComponent>(), nullptr);
}

TEST(Entity, ComponentTypeIsUnique) {
    Entity entity;
    entity.addComponent<HealthComponent>(3);
    EXPECT_EQ(entity.addComponent<HealthComponent>(99), nullptr);
    EXPECT_EQ(entity.getComponent<HealthComponent>()->getHealth(), 3);
}

TEST(Entity, BaseComponentsRequired) {
    EntityManager manager;
    EntityPtr ship = makeShip(manager, "player 1", 100, 100);
    EXPECT_FALSE(ship->hasBaseComponents());  // no PlayerComponent yet
    ship->addComponent<PlayerComponent>(true);
    EXPECT_TRUE(ship->hasBaseComponents());
}

TEST(EntityManager, CreateFindDestroy) {
    EntityManager manager;
    EntityPtr ship = makeShip(manager, "player 1", 0, 0);
    makeShip(manager, "enemy 2", 0, 0);

    EXPECT_EQ(manager.getEntities().size(), 2U);
    EXPECT_EQ(manager.getEntity("player 1"), ship);
    EXPECT_EQ(manager.getEntity("missing"), nullptr);

    manager.destroyEntity(ship);
    EXPECT_EQ(manager.getEntities().size(), 1U);
    EXPECT_EQ(manager.getEntity("player 1"), nullptr);
}

// Each direction must move along one axis only.
TEST(EntityMovement, EachDirectionMovesOneAxis) {
    EntityManager manager;
    EntityPtr ship = makeShip(manager, "player 1", 100, 100);

    ship->move(Direction::LEFT, {}, WIDTH, HEIGHT);
    EXPECT_EQ(position(ship), std::make_pair(95, 100));
    ship->move(Direction::RIGHT, {}, WIDTH, HEIGHT);
    EXPECT_EQ(position(ship), std::make_pair(100, 100));
    ship->move(Direction::DOWN, {}, WIDTH, HEIGHT);
    EXPECT_EQ(position(ship), std::make_pair(100, 105));
    ship->move(Direction::UP, {}, WIDTH, HEIGHT);
    EXPECT_EQ(position(ship), std::make_pair(100, 100));
    EXPECT_FALSE(ship->getDeathStatus());
}

TEST(EntityMovement, LeavingTheScreenKills) {
    EntityManager manager;
    EntityPtr ship = makeShip(manager, "player 1", 2, 100);
    ship->move(Direction::LEFT, {}, WIDTH, HEIGHT);
    EXPECT_TRUE(ship->getDeathStatus());
}

TEST(EntityCollision, ProjectileDamagesShipAndIsDestroyed) {
    EntityManager manager;
    EntityPtr ship = makeShip(manager, "player 1", 100, 100, 100);
    EntityPtr bullet = makeShip(manager, "bullet 9", 100, 95);
    bullet->addComponent<DamageComponent>(30);

    ship->move(Direction::UP, manager.getEntities(), WIDTH, HEIGHT);

    EXPECT_TRUE(bullet->getDeathStatus());
    EXPECT_FALSE(ship->getDeathStatus());
    EXPECT_EQ(ship->getComponent<HealthComponent>()->getHealth(), 70);
}

TEST(EntityCollision, LethalDamageKills) {
    EntityManager manager;
    EntityPtr ship = makeShip(manager, "player 1", 100, 100, 20);
    EntityPtr bullet = makeShip(manager, "bullet 9", 100, 95);
    bullet->addComponent<DamageComponent>(30);

    ship->move(Direction::UP, manager.getEntities(), WIDTH, HEIGHT);
    EXPECT_TRUE(ship->getDeathStatus());
}

TEST(EntityCollision, DistantEntitiesDoNotCollide) {
    EntityManager manager;
    EntityPtr ship = makeShip(manager, "player 1", 100, 100);
    makeShip(manager, "enemy 2", 400, 400);

    ship->move(Direction::UP, manager.getEntities(), WIDTH, HEIGHT);
    EXPECT_FALSE(ship->getDeathStatus());
    EXPECT_EQ(ship->getComponent<HealthComponent>()->getHealth(), 100);
}
