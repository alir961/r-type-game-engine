#pragma once
#include "GraphicBullet.hpp"
#include "GraphicMonster.hpp"
#include "GraphicStarship.hpp"
#include "engine/ecs/Entity.hpp"

namespace RType {

    class GraphicEntityFactory {
    public:
        static std::shared_ptr<GraphicBullet> createGraphicBullet(Entity &entity);
        static std::shared_ptr<GraphicMonster> createGraphicMonster(Entity &entity);
        static std::shared_ptr<GraphicStarship> createGraphicStarship(Entity &entity);
    };
};// namespace RType