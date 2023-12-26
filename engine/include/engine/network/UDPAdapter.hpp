/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <string>
#include <boost/asio.hpp>
#include "NetworkMessage.hpp"

namespace asio = boost::asio;

using UDP = asio::ip::udp;

namespace RType {

    constexpr std::size_t BUFFER_SIZE = 1024;

    using ReceiveCallback = std::function<void(const boost::system::error_code &error, std::size_t bytes_received)>;
    using DataBuffer = std::array<char, BUFFER_SIZE>;
    using MessageBuffer = std::array<std::byte, sizeof(RType::Message)>;

    class UDPAdapter {
    private:
        UDP::socket &_socket;
        UDP::endpoint &_remoteEndpoint;
        DataBuffer _dataBuffer{};
        MessageBuffer _messageBuffer{};

    protected:
        static void errorFunction(const boost::system::error_code &error, std::size_t);

    public:
        explicit UDPAdapter(UDP::socket &socket, UDP::endpoint &endpoint) :
                _socket(socket), _remoteEndpoint(endpoint) {}

        void sendData(const std::string &data);
        void sendData(const asio::const_buffer &data);
        void sendData(const Message &message);

        void receiveData(ReceiveCallback callback);
        void receiveMessage(ReceiveCallback callback);

        [[nodiscard]] const DataBuffer &getDataBuffer() const;
        [[nodiscard]] const MessageBuffer &getMessageBuffer() const;
    };

}
