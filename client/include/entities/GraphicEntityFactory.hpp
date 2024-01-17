#pragma once
#include "GraphicEntity.hpp"

namespace RType {
    /**
    * @brief Graphic Entity Factory base class.
    */
    class GraphicEntityFactory {
    public:
        static std::shared_ptr<GraphicEntity> createGraphicEntity(EntityPtr &entity, const std::string entityName) {
            return std::make_shared<GraphicEntity>(entity, entityName);
        }
    };
}
