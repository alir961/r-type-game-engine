/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <map>

/**
 * @brief Base class for position component.
 */
class PositionComponent {
public:
    /**
     * @brief Base constructor for position component.
     * @param position The position of the entity.
     */
    PositionComponent(std::pair<int, int> position) : _position(position) {}

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
    std::pair<int, int> getPositions() {
        return _position;
    }

private:
    std::pair<int, int> _position; /**< Position of the entity. */
};
