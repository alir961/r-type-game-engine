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
        /**
         * Setup an UDP server that allow clients connection
         *
         * @param ioContext The context of the server
         * @param endpoint The connection endpoint to the server
         */
        UDPServer(uint16_t port);

        /**
         * Stop the server and close the socket
         */
        ~UDPServer();

    private:
        UDPAdapter _adapter;
        GameLogic _game;
        MessageParser _parser = MessageParser(&_game, &_adapter);

        /**
         * Start receive data from clients
         */
        void startReceive();

        /**
         * Parse the received buffer data
         *
         * @param bytesReceived The number of bytes received
         */
        void handleReceive(std::size_t bytesReceived);

    };

}
