/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <engine/network/UDPAdapter.hpp>
#include "Client.hpp"

namespace RType {

    class Sessions {
    private:
        std::map<int, std::shared_ptr<Client>> _sessionMap;
        int _lastSessionID = 0;
    public:
        Sessions() = default;

        void setLastSessionID(int sessionID) {_lastSessionID = sessionID;};
        int setNewSession();

        std::shared_ptr<Client> getClientEndpoint(int sessionId);
    };
}
