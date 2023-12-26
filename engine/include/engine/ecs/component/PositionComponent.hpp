/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include <map>
#include "./AComponent.hpp"

namespace RType {
    /**
    * @brief Base class for position component.
    */
    class PositionComponent : public AComponent {
    public:
        /**
        * @brief Base constructor for position component.
        * @param position The position of the entity.
        */
        explicit PositionComponent(std::pair<int, int> position) : _position(std::move(position)) {}

        /**
        * @brief Set the position of the entity.
        * @param position A map representing the position coordinates.
        */
        void setPositions(std::pair<int, int> position) {
            _position = position;
        }

        /**
        * @brief Get the position of the entity.
        * @return A map representing the position coordinates.
        */
        [[nodiscard]] std::pair<int, int> getPositions() const {
            return _position;
        }

        /**
        * @brief Update the component.
        */
        void update() override {
            std::cout << "Component update\n";
        }

    private:
        std::pair<int, int> _position; /**< Position of the entity. */
    };
}
