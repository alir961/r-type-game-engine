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
    * @brief Base class for player component.
    */
    class PlayerComponent : public AComponent {
    public:
        /**
        * @brief Base constructor for player component.
        * @param isPlayer The status of the entity (player or not).
        */
        explicit PlayerComponent(bool isPlayer) : _isPlayer(isPlayer) {}

        /**
        * @brief Check if the entity is controlled by a player.
        * @return True if the entity is controlled by a player, false otherwise.
        */
        [[nodiscard]] bool getIsPlayer() const {
            return _isPlayer;
        }

        /**
        * @brief Update the component.
        */
        void update() override {
            std::cout << "Component update\n";
        }

    private:
        bool _isPlayer; /**< Flag indicating if the entity is controlled by a player. */
    };
}
