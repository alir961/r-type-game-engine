/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include <iostream>
#include <boost/asio.hpp>
#include "../include/UDPAdapter.hpp"

void RType::UDPAdapter::errorFunction(const boost::system::error_code &error, std::size_t) {
    if (error)
        std::cerr << "Error sending data: " << error.message() << "\n";
}

void RType::UDPAdapter::sendData(const std::string &data) {
    _socket.async_send_to(asio::buffer(data), _remoteEndpoint, errorFunction);
}

void RType::UDPAdapter::sendData(const asio::const_buffer &data) {
    _socket.async_send_to(data, _remoteEndpoint, errorFunction);
}


