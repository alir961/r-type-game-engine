#pragma once
#include "GraphicEntity.hpp"

namespace RType {
    /**
    * @brief Graphic Entity Factory base class.
    */
    class GraphicEntityFactory {
    public:
        static GraphicEntityPtr createStarship(EntityPtr &entity, const std::string entityName) {
            return std::make_shared<GraphicEntity>(entity, "client/assets/sprites/player.png", entityName);
        }

        static GraphicEntityPtr createBullet(EntityPtr &entity, const std::string entityName) {
            return std::make_shared<GraphicEntity>(entity, "client/assets/sprites/player_bullet.png", entityName);
        }

        static GraphicEntityPtr createMonster(EntityPtr &entity, const std::string entityName) {
            return std::make_shared<GraphicEntity>(entity, "client/assets/sprites/monster.png", entityName);
        }

        static GraphicEntityPtr createStatic(EntityPtr &entity, const std::string entityName) {
            return std::make_shared<GraphicEntity>(entity, "client/assets/sprites/mine.png", entityName);
        }

        static GraphicEntityPtr createBulletStarship(EntityPtr &entity, const std::string entityName) {
            return std::make_shared<GraphicEntity>(entity, "client/assets/sprites/enemy_bullet.png", entityName);
        }

        static GraphicEntityPtr createEnemyStarship(EntityPtr &entity, const std::string entityName) {
            return std::make_shared<GraphicEntity>(entity, "client/assets/sprites/enemy_starship.png", entityName);
        }
    };
}
