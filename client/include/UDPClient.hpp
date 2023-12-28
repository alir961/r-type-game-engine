/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#pragma once

#include <engine/network/UDPAdapter.hpp>
#include <iostream>

namespace RType {
    class UDPClient {
    public:
        using MessageHandlerFunction = std::function<void(const Message&)>;
        UDPClient(asio::io_context &io_context, UDP::endpoint endpoint);
        void startReceive();
    private:

        void handleReceive(std::size_t bytesReceived);

        UDP::socket _socket;
        UDPAdapter _adapter;
        std::unordered_map<MessageType, MessageHandlerFunction> _handlers;

        void handleConnectCallbackMessage(const Message& receiveMessage);
        void handleUnknownMessageType(const Message& receiveMessage);

    };
}