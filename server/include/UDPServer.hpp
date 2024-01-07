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

namespace RType {

    class UDPServer {
    public:

        UDPServer(asio::io_context &io_context, const UDP::endpoint &endpoint);

        ~UDPServer();

        using MessageHandlerFunction = std::function<void(const Message&)>;

    private:
        void startReceive();

        void handleReceive(std::size_t bytesReceived);

        void sendMessage(MessageType type, const std::string_view &data);

        EntityPtr createPlayerEntity();

        UDP::socket _socket;
        UDP::endpoint _remoteEndpoint;
        UDPAdapter _adapter;
        SessionManager _sessions;
        EntityManager _entityManager;
        std::unordered_map<MessageType, MessageHandlerFunction> _handlers;

        void handleConnectMessage(const Message& receiveMessage);
        void handleUnknownMessageType(const Message& receiveMessage);
        void handlePlayerNameMessageType(const Message& receiveMessage);
        void handleMoveLeftMessageType(const Message& receiveMessage);
        void handleMoveRightMessageType(const Message& receiveMessage);
        void handleMoveDownMessageType(const Message& receiveMessage);
        void handleMoveUpMessageType(const Message& receiveMessage);
    };

}
