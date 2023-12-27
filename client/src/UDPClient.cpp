/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#include "../include/UDPClient.hpp"

void RType::UDPClient::startReceive() {
    auto receiveData = [this](const boost::system::error_code &error, std::size_t bytes_received) {
        std::cout << "Receive " << bytes_received << "bytes!\n";
        if (!error)
            handleReceive(bytes_received);
        else std::cout << "Error receiving message: " << error.message() << "\n";
        startReceive();
    };
    _adapter.receiveMessage(receiveData);
}

void RType::UDPClient::handleReceive(std::size_t bytesReceived) {
    const MessageBuffer &buffer = _adapter.getMessageBuffer();
    const std::vector<std::byte> receivedData(buffer.begin(), buffer.begin() + bytesReceived);
    const Message receiveMessage = Message::deserialize(receivedData);

    std::cout << "Data: ";
    for (char character : receiveMessage.data) {
        std::cout << character;
    }
    std::cout << std::endl;
    _adapter.sendData(asio::buffer(buffer.data(), bytesReceived));
}

RType::UDPClient::UDPClient(asio::io_context &io_context, UDP::endpoint endpoint) :
    _socket(io_context, UDP::endpoint(UDP::v4(), 0)),
    _adapter(_socket, endpoint) {
    const RType::Message message = RType::NetworkMessageBuilder(RType::MessageType::CONNECT)
            .setData("")
            .build();

    _adapter.sendData(message);
    startReceive();
}
