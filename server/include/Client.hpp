/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#pragma once


#include <iostream>

namespace RType {
    class Client {
    private:
        std::string _playerName;
    public:
        Client() = default;

        void setPlayerName(const std::string &playerName) {_playerName = playerName;};

        [[nodiscard]] std::string getPlayerName() const {return _playerName;};
    };
}
