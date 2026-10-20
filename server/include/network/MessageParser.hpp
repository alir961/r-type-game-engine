/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "engine/network/NetworkMessage.hpp"
#include "engine/network/UDPAdapter.hpp"
#include "../SessionManager.hpp"
#include "../game/GameLogic.hpp"

namespace RType {

    using MessageHandlerFunction = std::function<void(const Message&)>;

    class MessageParser {
    private:
        std::unordered_map<MessageType, MessageHandlerFunction> _handlers;
        GameLogic *_game;
        UDPAdapter *_adapter;
        SessionManager *_sessions;
        UDP::endpoint _sender; /**< Address of the packet being handled. */

        /**
         * Find the session named in a message ("<type> <sessionID> ...") and record where it came from
         *
         * @return The session, or nullptr for an unknown or disconnected one
         */
        Session getSenderSession(const std::vector<std::string> &splitMessage);

        void handleConnectMessage(const Message &receiveMessage);

        void handleUnknownMessageType(const Message &receiveMessage);

        void handlePlayerNameMessageType(const Message &receiveMessage);

        void handlePlayerColor(const Message &receiveMessage);

        void handleMove(const Message &receiveMessage);

        void handlePlayerShoot(const RType::Message &receiveMessage);

        void handleTick(const RType::Message &receiveMessage);

        void handleDifficulty(const RType::Message &receiveMessage);

        void handleDisconnect(const RType::Message &receiveMessage);


    public:
        /**
         * Initialize a basic message parser that handle reactions to message
         *
         * @param game The game object
         * @param adapter The server UDP adapter
         */
        explicit MessageParser(GameLogic *game, UDPAdapter *adapter);

        /**
         * Parse a MessageBuffer and execute to corresponding reaction
         *
         * @param buffer The buffer to parse
         * @param bytesReceived The number of bytes received in the buffer
         */
        void parseMessage(const MessageBuffer &buffer, std::size_t bytesReceived);
    };

}