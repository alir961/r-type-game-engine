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
    private:
        void startReceive();

        void handleReceive(std::size_t bytesReceived) const;

        UDP::socket _socket;
        UDP::endpoint _remoteEndpoint;
        UDPAdapter _adapter;

    public:
        UDPClient(asio::io_context &io_context, UDP::endpoint endpoint);
    };
}