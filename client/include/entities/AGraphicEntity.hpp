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
        virtual EntityPtr getEntity() = 0;

        /**
        * @brief Return the _sprite of the graphical _entity
        */
        virtual sf::Sprite getSprite() = 0;

        /**
        * @brief Return the name of the graphical _entity
        */
        [[nodiscard]] std::string getEntityName() const {
            return _entityName;
        }

        void setEntityName(const std::string &entityName) {_entityName = entityName;};

        ~AGraphicEntity() override = default;
    };

    using GraphicEntityPtr = std::shared_ptr<AGraphicEntity>;

}
