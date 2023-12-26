#pragma once
#include "GraphicEntity.hpp"
#include "engine/ecs/Entity.hpp"

namespace RType {
    /**
    * @brief Graphic Entity Factory base class.
    */
    class GraphicEntityFactory {
    public:
        static std::shared_ptr<GraphicEntity> createGraphicEntity(std::shared_ptr<Entity> &entity) {
            return std::make_shared<GraphicEntity>(entity);
        }
    };
}
