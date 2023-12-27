/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <engine/network/UDPAdapter.hpp>
#include <iostream>
#include "SessionManager.hpp"

namespace RType {

    class UDPServer {
    public:

        UDPServer(asio::io_context &io_context, const UDP::endpoint &endpoint);

        ~UDPServer();

        using MessageHandlerFunction = std::function<void(const Message&)>;

    private:
        void startReceive();

        void handleReceive(std::size_t bytesReceived);

        UDP::socket _socket;
        UDP::endpoint _remoteEndpoint;
        UDPAdapter _adapter;
        SessionManager _sessions;
        std::unordered_map<MessageType, MessageHandlerFunction> _handlers;

        void handleConnectMessage(const Message& message);
        void handleUnknownMessageType(const Message& message);
    };

}
