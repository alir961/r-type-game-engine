#pragma once
#include "GraphicEntity.hpp"

namespace RType {
    /**
    * @brief Graphic Entity Factory base class.
    */
    class GraphicEntityFactory {
    public:
        static GraphicEntityPtr createStarship(EntityPtr &entity, const std::string entityName) {
            return std::make_shared<GraphicEntity>(entity, "client/assets/sprites/r-typesheet42.gif", entityName);
        }

        static GraphicEntityPtr createBullet(EntityPtr &entity, const std::string entityName) {
            return std::make_shared<GraphicEntity>(entity, "client/assets/sprites/r-typesheet2.gif", entityName);
        }

        static GraphicEntityPtr createMonster(EntityPtr &entity, const std::string entityName) {
            return std::make_shared<GraphicEntity>(entity, "client/assets/sprites/r-typesheet18.gif", entityName);
        }
    };
}
