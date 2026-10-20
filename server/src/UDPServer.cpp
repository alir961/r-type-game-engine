/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "../include/UDPServer.hpp"
#include <engine/network/NetworkMessage.hpp>

RType::UDPServer::UDPServer(uint16_t port, Difficulty difficulty) :
        _adapter("0.0.0.0", port),
        _game(&_adapter) {
    _game.setDifficulty(difficulty);
    startReceive();
    std::cout << "Starting server on " << "0.0.0.0" << ":" << port << "\n";
    _adapter.runContext();
}

RType::UDPServer::~UDPServer() {
    try {
        _adapter.closeSocket();
    } catch (std::exception &exception) {
        std::cerr << "Unable to close server socket: " << exception.what() << "\n";
    }
}

void RType::UDPServer::startReceive() {
    auto receiveData = [this](const asio::error_code &error, std::size_t bytes_received) {
        if (!error)
            handleReceive(bytes_received);
        else std::cerr << "Error receiving message: " << error.message() << "\n";
        startReceive();
    };

    _adapter.receiveMessage(receiveData);
}

void RType::UDPServer::handleReceive(std::size_t bytesReceived) {
    const MessageBuffer &buffer = _adapter.getMessageBuffer();

    _parser.parseMessage(buffer, bytesReceived);
}
