#include <gtest/gtest.h>

#include "ecs/EntityManager.hpp"

using namespace RType;

namespace {

    // Builds an entity with the components a ship needs.
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
