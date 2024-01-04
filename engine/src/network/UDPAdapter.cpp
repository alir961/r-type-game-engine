/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include <iostream>
#include "engine/network/UDPAdapter.hpp"

void RType::UDPAdapter::errorFunction(const asio::error_code &error, std::size_t bytes_send) {
    if (error)
        std::cerr << "Error sending data: " << error.message() << "\n";
    else std::cout << "UDPAdapter: " << bytes_send << "bytes send!\n";
}

void RType::UDPAdapter::sendData(const std::string &data) {
    _socket.async_send_to(asio::buffer(data), _remoteEndpoint, errorFunction);
}

void RType::UDPAdapter::sendData(const asio::const_buffer &data) {
    _socket.async_send_to(data, _remoteEndpoint, errorFunction);
}

void RType::UDPAdapter::sendData(const RType::Message &message) {
    std::vector<std::byte> data = message.serialize();

    _socket.async_send_to(asio::buffer(data), _remoteEndpoint, errorFunction);
}

void RType::UDPAdapter::receiveData(ReceiveCallback callback) {
    const auto &buffer = asio::buffer(_dataBuffer);

    _socket.async_receive_from(asio::buffer(buffer), _remoteEndpoint, callback);
}

void RType::UDPAdapter::receiveMessage(ReceiveCallback callback) {
    _socket.async_receive_from(asio::buffer(_messageBuffer), _remoteEndpoint, callback);
}

const RType::DataBuffer &RType::UDPAdapter::getDataBuffer() const {
    return _dataBuffer;
}

const RType::MessageBuffer &RType::UDPAdapter::getMessageBuffer() const {
    return _messageBuffer;
}


