/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#pragma once

#include <engine/network/UDPAdapter.hpp>
#include <engine/tools/Split.hpp>
#include <iostream>
#include "engine/tools/Thread.hpp"

namespace RType {

    /**
     * @brief Type alias for a message handler function.
     */
    using MessageHandlerFunction = std::function<void(const Message &)>;

    /**
     * @brief Class representing a UDP client for communication.
     */
    class UDPClient {
    public:
        /**
         * @brief Constructor for UDPClient.
         * @param hostname The hostname of the server.
         * @param port The port number for communication.
         * @param username The username associated with the client.
         */
        UDPClient(const std::string &hostname, int port, std::string username);

        ~UDPClient();

        /**
         * @brief Initiates the process to start receiving messages.
         */
        void startReceive();

        std::string getLastMessage();

        void sendMessage(MessageType type, const std::string_view &data);

        [[nodiscard]] int getClientID() const { return _clientID; };

        [[nodiscard]] bool isConnected() const { return _connected; };

    private:
        /**
         * @brief Sets up the message handlers for different message types.
         */
        void setupHandlers();

        /**
         * @brief Handles the received data.
         * @param bytesReceived The number of bytes received.
         */
        void handleReceive(std::size_t bytesReceived);

        std::string _username; ///< The username associated with the client.
        asio::io_context _context; ///< The IO context for asynchronous operations.
        UDP::endpoint _endpoint; ///< The endpoint for communication.
        UDP::socket _socket; ///< The UDP socket for communication.
        UDPAdapterPtr _adapter; ///< The UDP adapter for handling send/receive operations.
        RType::Thread _thread = RType::Thread(); ///< Thread for asynchronous operations.
        std::unordered_map<MessageType, MessageHandlerFunction> _handlers; ///< Map of message handlers.
        std::vector<std::string> _messageQueue;
        std::mutex _queueMutex;
        int _clientID = -1;
        bool _connected = false;
        bool _stop = false;

        /**
         * @brief Handles the connection callback message.
         * @param receiveMessage The received message.
         */
        void handleConnectCallbackMessage(const Message &receiveMessage);

        /**
         * @brief Handles the player name callback message.
         * @param receiveMessage The received message.
         */
        void handlePlayerNameCallbackMessageType(const Message &receiveMessage);

        /**
         * @brief Handles the move left callback message.
         * @param receiveMessage The received message.
         */
        void handleMoveLeftCallbackMessageType(const Message &receiveMessage);

        /**
         * @brief Handles the move right callback message.
         * @param receiveMessage The received message.
         */
        void handleMoveRightCallbackMessageType(const Message &receiveMessage);

        /**
         * @brief Handles the move down callback message.
         * @param receiveMessage The received message.
         */
        void handleMoveDownCallbackMessageType(const Message &receiveMessage);

        /**
         * @brief Handles the move up callback message.
         * @param receiveMessage The received message.
         */
        void handleMoveUpCallbackMessageType(const Message &receiveMessage);

    };

    /**
     * @brief Type alias for a shared pointer to UDPClient.
     */
    using UDPClientPtr = std::shared_ptr<UDPClient>;

}
