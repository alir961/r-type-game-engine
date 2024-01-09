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
#include "game/GameLogic.hpp"

namespace RType {

    class UDPServer {
    public:
        UDPServer(asio::io_context &ioContext, const UDP::endpoint &endpoint);

        ~UDPServer();

    private:
        UDP::socket _socket;
        UDP::endpoint _remoteEndpoint;
        UDPAdapter _adapter;
        GameLogic _game;
        MessageParser _parser = MessageParser(&_game, &_adapter);

        void startReceive();

        void handleReceive(std::size_t bytesReceived);
    };

}
