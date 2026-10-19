/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <map>
#include "./AComponent.hpp"
#include "../../modules/graphical/DataCommon.hpp"

namespace RType {

    /**
    * @brief Base class for position component.
    */
    class PositionComponent : public AComponent {
    public:
        /**
        * @brief Base constructor for position component.
        * @param position The position of the _entity.
        */
        explicit PositionComponent(Vector2f position) : _position(std::move(position)) {}

        /**
        * @brief Set the position of the _entity.
        * @param position A map representing the position coordinates.
        */
        void setPositions(Vector2f position) {
            _position = position;
        }

        /**
        * @brief Get the position of the _entity.
        * @return A map representing the position coordinates.
        */
        [[nodiscard]] Vector2f getPosition() const {
            return _position;
        }

        /**
        * @brief Update the component.
        */
        void update() override {
            std::cout << "Component update\n";
        }

    private:
        Vector2f _position = Vector2f(0.0F, 0.0F); /**< Position of the _entity. */
    };
}
