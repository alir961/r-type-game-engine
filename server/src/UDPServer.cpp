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
    auto data = std::string(_receiveBuffer.data(), bytes_received);

    std::cout << "Received message: '" << data << "'\n";
    if (data.starts_with("connect")) {
        const std::string sessionId = "id";

        _adapter.sendData("connect " + sessionId + " ok");
    } else _adapter.sendData(buffer);
}

RType::UDPServer::UDPServer(asio::io_context &io_context, const UDP::endpoint &endpoint) :
        _socket(io_context, endpoint),
        _adapter(_socket) {
    startReceive();
}

RType::UDPServer::~UDPServer() {
    try {
        _socket.close();
    } catch (std::exception &exception) {
        std::cerr << "Unable to close server socket: " << exception.what() << "\n";
    }
}
