/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#include "../include/SessionManager.hpp"

RType::Session RType::SessionManager::getClientSession(int sessionId) {
    auto session = _sessionMap.find(sessionId);
    if (session == _sessionMap.end())
        return {};
    return session->second;
}

int RType::SessionManager::getNextSessionId() {
    _sessionMap[_lastSessionID] = std::make_shared<Client>();
    return (_lastSessionID++);
}
