/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include "UDPAdapter.hpp"

namespace RType {

    constexpr std::size_t BUFFER_SIZE = 1024;

    class UDPServer {
    public:
        UDPServer(asio::io_context &io_context, const UDP::endpoint &endpoint);

        ~UDPServer();

    private:
        void startReceive();

        void handleReceive(std::size_t bytes_received);

        UDP::socket _socket;
        UDP::endpoint _remoteEndpoint;
        UDPAdapter _adapter;
        std::array<char, BUFFER_SIZE> _receiveBuffer{};
    };

}
