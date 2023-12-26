/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#include "../include/Sessions.hpp"

int RType::Sessions::setNewSession(const UDP::endpoint &udpEndpoint) {
    _sessionMap[_lastSessionID] = udpEndpoint;
    _lastSessionID += 1;
    return _lastSessionID - 1;
}

UDP::endpoint RType::Sessions::getClientEndpoint(int sessionId) {
    auto session = _sessionMap.find(sessionId);
    if (session == _sessionMap.end())
        return {};
    return session->second;
}
