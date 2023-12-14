/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include "./AComponent.hpp"

/**
 * @brief Base class for player component.
 */
class PlayerComponent : public AComponent {
public:
    /**
     * @brief Base constructor for player component.
     * @param isPlayer The status of the entity (player or not).
     */
    PlayerComponent(bool isPlayer) : _isPlayer(isPlayer) {}

    /**
     * @brief Check if the entity is controlled by a player.
     * @return True if the entity is controlled by a player, false otherwise.
     */
    bool getIsPlayer() {
        return _isPlayer;
    }

private:
    bool _isPlayer; /**< Flag indicating if the entity is controlled by a player. */
};
