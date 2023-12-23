#pragma once
#include "GraphicBullet.hpp"
#include "GraphicMonster.hpp"
#include "GraphicStarship.hpp"
#include "engine/ecs/Entity.hpp"

class GraphicEntityFactory {
public:
    static std::shared_ptr<GraphicBullet> createGraphicBullet(std::shared_ptr<Entity> &entity);
    static std::shared_ptr<GraphicMonster> createGraphicMonster(std::shared_ptr<Entity> &entity);
    static std::shared_ptr<GraphicStarship> createGraphicStarship(std::shared_ptr<Entity> &entity);
};