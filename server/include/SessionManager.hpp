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
#include <iostream>
#include "Client.hpp"
#include <engine/network/UDPAdapter.hpp>

namespace RType {

    class SessionManager {
    private:
        std::map<int, Session> _sessionMap;
        int _lastSessionID = 0;

    public:
        /**
         * Instantiate default SessionManager
         */
        SessionManager() = default;

        /**
         * Retrieve a free ID for the session
         *
         * @return The session ID
         */
        [[nodiscard]] int getNextSessionId();

        /**
         * Retrieve a Session associated with an ID
         *
         * @param sessionId The session ID
         * @return The session if find or nullptr
         */
        Session getClientSession(int sessionId);
    };
}
