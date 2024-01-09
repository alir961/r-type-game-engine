/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "../../include/network/MessageParser.hpp"
#include "../../include/SessionManager.hpp"
#include "engine/tools/Split.hpp"

RType::MessageParser::MessageParser(SessionManager *sessions) : _sessions(sessions) {
    _handlers[MessageType::CONNECT] = [this](const Message& msg) {handleConnectMessage(msg);};
    _handlers[MessageType::DISCONNECT] = [this](const Message& ) {sendMessage(MessageType::DISCONNECT, "");};
    _handlers[MessageType::UNKNOWN] = [this](const Message& msg) {handleUnknownMessageType(msg);};
    _handlers[MessageType::PLAYER_NAME] = [this](const Message& msg) {handlePlayerNameMessageType(msg);};
    _handlers[MessageType::MOVE_LEFT] = [this](const Message& msg) {handleMoveLeftMessageType(msg);};
    _handlers[MessageType::MOVE_RIGHT] = [this](const Message& msg) {handleMoveRightMessageType(msg);};
    _handlers[MessageType::MOVE_DOWN] = [this](const Message& msg) {handleMoveDownMessageType(msg);};
    _handlers[MessageType::MOVE_UP] = [this](const Message& msg) {handleMoveUpMessageType(msg);};
}

void RType::MessageParser::handleMoveLeftMessageType(const RType::Message &receiveMessage) {
    const std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    const RType::Session session = _sessions->getClientSession(sessionID);

    sendMessage(MessageType::MOVE_LEFT, std::format("move_left {} ok\n", sessionID));
}

void RType::MessageParser::handleMoveRightMessageType(const RType::Message &receiveMessage) {
    const std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    const RType::Session session = _sessions->getClientSession(sessionID);

    sendMessage(MessageType::MOVE_RIGHT, std::format("move_right {} ok\n", sessionID));
}

void RType::MessageParser::handleMoveDownMessageType(const RType::Message &receiveMessage) {
    const std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    const RType::Session session = _sessions->getClientSession(sessionID);

    sendMessage(MessageType::MOVE_DOWN, std::format("move_down {} ok\n", sessionID));
}

void RType::MessageParser::handleMoveUpMessageType(const RType::Message &receiveMessage) {
    const std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage[1]);
    const RType::Session session = _sessions->getClientSession(sessionID);

    sendMessage(MessageType::MOVE_DOWN, std::format("move_up {} ok\n", sessionID));
}

void RType::MessageParser::handleConnectMessage(const RType::Message &) {
    int sessionId = _sessions->getNextSessionId();

    std::cout << "New connection! SessionId: " << sessionId << "!\n";
    sendMessage(MessageType::CONNECT_CALLBACK, std::format("connect {} ok", sessionId));
}

void RType::MessageParser::handleUnknownMessageType(const RType::Message &) {
    std::cout << "Unknown Message!\n";
}

void RType::MessageParser::handlePlayerNameMessageType(const RType::Message &receiveMessage) {
    const std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    const int sessionID = std::stoi(splitMessage[1]);
    const std::string playerName = splitMessage[2];
    const RType::Session session = _sessions->getClientSession(sessionID);

    session->setPlayerName(playerName);
    session->setPlayerEntity(createPlayerEntity(sessionID));
}

void RType::MessageParser::parseMessage(const RType::MessageBuffer &buffer, std::size_t bytesReceived) {
    const std::vector<std::byte> receivedData(buffer.begin(), buffer.begin() + bytesReceived);
    const Message receiveMessage = Message::deserialize(receivedData);
    auto handlerIt = _handlers.find(receiveMessage.type);

    if (handlerIt != _handlers.end())
        handlerIt->second(receiveMessage);
    else
        handleUnknownMessageType(receiveMessage);
}

void RType::MessageParser::sendMessage(MessageType type, const std::string_view &data) {
    const RType::Message response = RType::NetworkMessageBuilder(type)
        .setData(data)
        .build();
    const std::vector<std::byte> binaryData = response.serialize();

    _adapter.sendData(asio::buffer(binaryData));
}

RType::EntityPtr RType::MessageParser::createPlayerEntity(int sessionID) {
    const std::string message = std::format("player {} speed 10 health 100 position 300 30 size 2 2", sessionID);
    EntityPtr playerEntity = _factory.createDefaultPlayer();

    sendMessage(MessageType::PLAYER_NAME, message);
    return playerEntity;
}
