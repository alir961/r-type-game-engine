/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#include "../include/Sessions.hpp"

RType::Session RType::Sessions::getClientEndpoint(int sessionId) {
    auto session = _sessionMap.find(sessionId);
    if (session == _sessionMap.end())
        return {};
    return session->second;
}

int RType::Sessions::setNewSession() {
    _sessionMap[_lastSessionID] = std::make_shared<Client>();
    _lastSessionID += 1;
    return _lastSessionID - 1;
}
