/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** IGraphicEntity.hpp
*/

#pragma once
#include "IGraphicEntity.hpp"

namespace RType {

    /**
    * @brief Graphic Entity abstraction from the interface IGraphicEntity.
    */
    class AGraphicEntity : public IGraphicEntity {
    private:
        std::string _entityName; /**< Entity name. */

    public:
        explicit AGraphicEntity(std::string entityName) : _entityName(std::move(entityName)) {}

        /**
        * @brief Return the _entity of the graphical _entity
        */
        [[nodiscard]] virtual EntityPtr getEntity() = 0;

        /**
        * @brief Return the _playerSprite of the graphical _entity
        */
        [[nodiscard]] virtual SpriteComponent getSprite() = 0;

        /**
        * @brief Return the name of the graphical _entity
        */
        [[nodiscard]] std::string getEntityName() const {
            return _entityName;
        }
    };

    using GraphicEntityPtr = std::shared_ptr<AGraphicEntity>;

}
