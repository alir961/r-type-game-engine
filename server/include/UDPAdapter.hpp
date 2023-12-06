/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <string>

namespace asio = boost::asio;

using UDP = asio::ip::udp;

namespace RType {

    class UDPAdapter {
    private:
        UDP::socket &_socket;
        UDP::endpoint _remoteEndpoint;

    protected:
        static void errorFunction(const boost::system::error_code &error, std::size_t);

    public:
        explicit UDPAdapter(UDP::socket &socket) :
                _socket(socket) {}

        void sendData(const std::string &data);
        void sendData(const asio::const_buffer &data);
    };

}
