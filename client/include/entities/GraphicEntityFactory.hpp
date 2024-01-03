#pragma once
#include "GraphicEntity.hpp"
#include "engine/ecs/Entity.hpp"

namespace RType {
    /**
    * @brief Graphic Entity Factory base class.
    */
    class GraphicEntityFactory {
    public:
        static std::shared_ptr<GraphicEntity> createGraphicEntity(EntityPtr &entity, const std::string &path, const std::string entityName) {
            return std::make_shared<GraphicEntity>(entity, path, entityName);
        }
    };
}
