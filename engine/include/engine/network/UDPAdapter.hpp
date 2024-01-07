/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <string>
#include <asio.hpp>
#include <functional>
#include "NetworkMessage.hpp"

using UDP = asio::ip::udp;

namespace RType {

    /**
     * @brief Size of the buffer used for receiving and sending data.
     */
    constexpr std::size_t BUFFER_SIZE = 1024;

    /**
     * @brief Callback function type for handling asynchronous receive operations.
     */
    using ReceiveCallback = std::function<void(const asio::error_code &error, std::size_t bytes_received)>;

    /**
     * @brief Buffer type for storing received or to-be-sent data.
     */
    using DataBuffer = std::array<char, BUFFER_SIZE>;

    /**
     * @brief Buffer type for storing received messages.
     */
    using MessageBuffer = std::array<std::byte, sizeof(RType::Message)>;

    /**
     * @brief Represents a UDP adapter for handling communication over UDP.
     */
    class UDPAdapter {
    private:
        UDP::socket &_socket;
        UDP::endpoint &_remoteEndpoint;
        DataBuffer _dataBuffer{};
        MessageBuffer _messageBuffer{};

    protected:
        /**
         * @brief Static error handling function for asynchronous operations.
         * @param error The error code.
         * @param bytesReceived The number of bytes received.
         */
        static void errorFunction(const asio::error_code &error, std::size_t);

    public:
        /**
         * @brief Constructor for UDPAdapter.
         * @param socket Reference to the UDP socket.
         * @param endpoint Reference to the remote endpoint.
         */
        explicit UDPAdapter(UDP::socket &socket, UDP::endpoint &endpoint) :
                _socket(socket), _remoteEndpoint(endpoint) {}

        /**
        * @brief Sends string data over the UDP connection.
        * @param data The string data to send.
        */
        void sendData(const std::string &data);

        /**
         * @brief Sends data over the UDP connection using an asio buffer.
         * @param data The asio buffer containing the data.
         */
        void sendData(const asio::const_buffer &data);

        /**
         * @brief Sends a message over the UDP connection.
         * @param message The message to send.
         */
        void sendData(const Message &message);

        /**
         * @brief Receives data asynchronously and invokes the callback upon completion.
         * @param callback The callback function to handle received data.
         */
        void receiveData(ReceiveCallback callback);

        /**
         * @brief Receives a message asynchronously and invokes the callback upon completion.
         * @param callback The callback function to handle received messages.
         */
        void receiveMessage(ReceiveCallback callback);

        /**
         * @brief Gets the current data buffer.
         * @return The data buffer.
         */
        [[nodiscard]] const DataBuffer &getDataBuffer() const;

        /**
         * @brief Gets the current message buffer.
         * @return The message buffer.
         */
        [[nodiscard]] const MessageBuffer &getMessageBuffer() const;
    };

    using UDPAdapterPtr = std::shared_ptr<UDPAdapter>;

}
