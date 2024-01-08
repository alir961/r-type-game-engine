/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include "./AComponent.hpp"

namespace RType {
    /**
     * @brief Base class for collision component.
    */
    class SizeRectComponent : public AComponent {
    public:
        /**
         * @brief Base constructor for collidable component.
        * @param isCollidable The status of the _entity (collidable or not).
        */
        explicit SizeRectComponent(float width, float height) : _width(width), _height(height) {}

        /**
        * @brief Set the collision status of the _entity.
        * @param isCollidable True if the _entity is collidable, false otherwise.
        */
        void setSize(float width, float height) {
            _width = width;
            _height = height;
        }

        /**
        * @brief Get the collision status of the _entity.
        * @return True if the _entity is collidable, false otherwise.
        */
        [[nodiscard]] std::pair<float, float> getSize() const {
            return std::make_pair(_width, _height);
        }

        /**
        * @brief Update the component.
        */
        void update() override {
            std::cout << "Component update\n";
        }

    private:
        float _width, _height; /**< Size of the _entity. */
    };
}
