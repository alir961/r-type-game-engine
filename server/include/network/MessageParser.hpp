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

        void handleConnectMessage(const Message &receiveMessage);

        void handleUnknownMessageType(const Message &receiveMessage);

        void handlePlayerNameMessageType(const Message &receiveMessage);

        void handleMove(const Message &receiveMessage);

        void sendMessage(MessageType type, const std::string_view &data);

        EntityPtr createPlayerEntity(int sessionID);

        static Direction getDirection(MessageType type);

    public:
        explicit MessageParser(GameLogic *game, UDPAdapter *adapter);

        void parseMessage(const MessageBuffer &buffer, std::size_t bytesReceived);
    };

}