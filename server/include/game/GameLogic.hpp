/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../SessionManager.hpp"

namespace RType {

    class GameLogic {
    private:


    public:
        EntityPtr createPlayerEntity(int sessionID) {
            EntityPtr playerEntity = _factory.createDefaultPlayer();

            return playerEntity;
        }
    };

}
