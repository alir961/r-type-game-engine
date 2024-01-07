/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#pragma once


#include <iostream>
#include <engine/ecs/Entity.hpp>

namespace RType {
    class Client {
    private:
        std::string _playerName;
        EntityPtr  _playerEntity;
    public:
        Client() = default;

        void setPlayerName(const std::string &playerName) {_playerName = playerName;};

        void setPlayerEntity(const EntityPtr &playerEntity) {_playerEntity = playerEntity;};

        [[nodiscard]] std::string getPlayerName() const {return _playerName;};
    };
}
