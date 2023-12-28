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

    using Session = std::shared_ptr<Client>;

    class SessionManager {
    private:
        std::map<int, Session> _sessionMap;
        int _lastSessionID = 0;
    public:
        SessionManager() = default;

        void setLastSessionID(int sessionID) {_lastSessionID = sessionID;};
        int setNewSession();

        Session getClientSession(int sessionId);
    };
}
