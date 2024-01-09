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
        * @param isPlayer The status of the _entity (player or not).
        */
        explicit PlayerComponent(bool isPlayer) : _isPlayer(isPlayer) {}

        /**
        * @brief Check if the _entity is controlled by a player.
        * @return True if the _entity is controlled by a player, false otherwise.
        */
        [[nodiscard]] bool getIsPlayer() const {
            return _isPlayer;
        }

        /**
        * @brief Check the _entity score.
        * @return score number.
        */
        [[nodiscard]] int getScore() const {
            return _score;
        }

        /**
        * @brief Set the score.
        */
        void setScore(int score) {
            _score = score;
        }

        /**
        * @brief Set the username.
        */
        void setUserName(std::string username) {
            _username = username;
        }

        /**
        * @brief Update the component.
        */
        void update() override {
            std::cout << "Component update\n";
        }

        /**
        * @brief Get the username.
        */
        [[nodiscard]] std::string getUserName() const {
            if (_isPlayer)
                return _username;
            return "";
        }

    private:
        bool _isPlayer; /**< Flag indicating if the _entity is controlled by a player. */
        int _score = 0; /**< Int indicating the _entity score. */
        std::string _username;
    };
}
