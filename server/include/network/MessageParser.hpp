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

namespace RType {

    using MessageHandlerFunction = std::function<void(const Message&)>;

    class MessageParser {
    private:
        std::unordered_map<MessageType, MessageHandlerFunction> _handlers;
        SessionManager *_sessions;

        void handleConnectMessage(const Message &receiveMessage);

        void handleUnknownMessageType(const Message &receiveMessage);

        void handlePlayerNameMessageType(const Message &receiveMessage);

        void handleMoveLeftMessageType(const Message &receiveMessage);

        void handleMoveRightMessageType(const Message &receiveMessage);

        void handleMoveDownMessageType(const Message &receiveMessage);

        void handleMoveUpMessageType(const Message &receiveMessage);

        void sendMessage(MessageType type, const std::string_view &data);

        EntityPtr createPlayerEntity(int sessionID);

    public:
        explicit MessageParser(SessionManager *sessions);

        void parseMessage(const MessageBuffer &buffer, std::size_t bytesReceived);
    };

}