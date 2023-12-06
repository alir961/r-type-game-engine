/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "../include/UDPServer.hpp"

void RType::UDPServer::startReceive() {
    const auto &buffer = boost::asio::buffer(_receiveBuffer);
    auto receiveData = [this](const boost::system::error_code &error, std::size_t bytes_received) {
        std::cout << "Receive " << bytes_received << "bytes!\n";
        if (!error)
            handleReceive(bytes_received);
        else std::cerr << "Error receiving message: " << error.message() << "\n";
        startReceive();
    };

    _socket.async_receive_from(buffer, _remoteEndpoint, receiveData);
}

void RType::UDPServer::handleReceive(std::size_t bytes_received) {
    const auto &buffer = boost::asio::buffer(_receiveBuffer.data(), bytes_received);
    auto errorFunction = [](const boost::system::error_code &error, std::size_t /*bytes_sent*/) {
        if (error)
            std::cerr << "Error sending echo message: " << error.message() << "\n";
    };

    std::cout << "Received message: " << std::string(_receiveBuffer.data(), bytes_received) << "\n";
    _socket.async_send_to(buffer, _remoteEndpoint, errorFunction);
}

RType::UDPServer::UDPServer(asio::io_context &io_context, const UDP::endpoint &endpoint) :
        _socket(io_context, endpoint) {
    startReceive();
}
