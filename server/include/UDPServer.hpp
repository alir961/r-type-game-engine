/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <engine/network/UDPAdapter.hpp>
#include <engine/tools/Split.hpp>
#include <engine/ecs/EntityManager.hpp>
#include <iostream>
#include "SessionManager.hpp"
#include "network/MessageParser.hpp"
#include "game/EntityFactory.hpp"

namespace RType {

    class UDPServer {
    public:
        UDPServer(asio::io_context &io_context, const UDP::endpoint &endpoint);

        ~UDPServer();

    private:
        UDP::socket _socket;
        UDP::endpoint _remoteEndpoint;
        UDPAdapter _adapter;
        SessionManager _sessions;
        EntityManager _entityManager;
        MessageParser _parser = MessageParser(&_sessions);
        EntityFactory _factory = EntityFactory(&_entityManager);

        void startReceive();

        void handleReceive(std::size_t bytesReceived);
    };

}
