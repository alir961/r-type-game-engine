/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "../../include/network/MessageParser.hpp"
#include "engine/tools/Split.hpp"

RType::MessageParser::MessageParser(GameLogic *game, UDPAdapter *adapter) :
        _game(game),
        _adapter(adapter),
        _sessions(&game->getSessionManager()) {
    _handlers[MessageType::CONNECT] = [this](const Message &msg) { handleConnectMessage(msg); };
    _handlers[MessageType::UNKNOWN] = [this](const Message &msg) { handleUnknownMessageType(msg); };
    _handlers[MessageType::PLAYER_NAME] = [this](const Message &msg) { handlePlayerNameMessageType(msg); };
    _handlers[MessageType::MOVE_LEFT] = [this](const Message &msg) { handleMove(msg); };
    _handlers[MessageType::MOVE_RIGHT] = [this](const Message &msg) { handleMove(msg); };
    _handlers[MessageType::MOVE_DOWN] = [this](const Message &msg) { handleMove(msg); };
    _handlers[MessageType::MOVE_UP] = [this](const Message &msg) { handleMove(msg); };
    _handlers[MessageType::SHOOT] = [this](const Message &msg) { handlePlayerShoot(msg); };
    _handlers[MessageType::PLAYER_COLOR] = [this](const Message &msg) { handlePlayerColor(msg); };
    _handlers[MessageType::TICK] = [this](const Message &msg) { handleTick(msg); };
    _handlers[MessageType::DISCONNECT] = [this](const Message &msg) { handleDisconnect(msg); };
    _handlers[MessageType::DIFFICULTY] = [this](const Message &msg) { handleDifficulty(msg); };
}

void RType::MessageParser::handleConnectMessage(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    float windowWidth = std::stof(splitMessage.at(1));
    float windowHeight = std::stof(splitMessage.at(2));
    int sessionId = _sessions->getNextSessionId();
    std::shared_ptr<Client> session = _sessions->getClientSession(sessionId);

    session->setEndpoint(_sender);
    session->setWindowWidth(windowWidth);
    session->setWindowHeight(windowHeight);
    if (_sessions->getWindowWidth() < windowWidth)
        _sessions->setWindowWidth(windowWidth);
    if (_sessions->getWindowHeight() < windowHeight)
        _sessions->setWindowHeight(windowHeight);
    std::cout << "New connection! SessionId: " << sessionId << "!\n";
    char buffer[50];
    sprintf(buffer, "connect %d ok", sessionId);
    _game->sendTo(sessionId, MessageType::CONNECT_CALLBACK, buffer);
}

void RType::MessageParser::handleUnknownMessageType(const RType::Message &) {
    std::cout << "Unknown Message!\n";
}

RType::Session RType::MessageParser::getSenderSession(const std::vector<std::string> &splitMessage) {
    const Session session = _sessions->getClientSession(std::stoi(splitMessage.at(1)));

    // Remember where this player's packets come from: its updates are sent back there.
    if (session != nullptr)
        session->setEndpoint(_sender);
    return session;
}

void RType::MessageParser::handlePlayerNameMessageType(const RType::Message &receiveMessage) {
    const std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    const RType::Session session = getSenderSession(splitMessage);
    const int sessionID = std::stoi(splitMessage[1]);

    if (session == nullptr)
        return;
    session->setPlayerName(splitMessage.at(2));
    if (session->getEntity() == nullptr)
        session->setPlayerEntity(_game->createPlayerEntity(sessionID, session));
    _game->sendAllEntities(sessionID);
}

void RType::MessageParser::handleMove(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    Session session = getSenderSession(splitMessage);

    if (session == nullptr || session->getEntity() == nullptr)
        return;
    EntityPtr entity = session->getEntity();
    _game->movePlayer(_game->getDirection(receiveMessage.type), entity);
    _game->sendPlayerDetails(entity);
    _game->checkEntitiesStatus();
}

void RType::MessageParser::parseMessage(const RType::MessageBuffer &buffer, std::size_t bytesReceived) {
    const std::vector<std::byte> receivedData(buffer.begin(), buffer.begin() + bytesReceived);
    const Message receiveMessage = Message::deserialize(receivedData);
    auto handlerIt = _handlers.find(receiveMessage.type);
    // The game loop runs on its own thread: never touch the world at the same time.
    const auto guard = _game->lock();

    _sender = _adapter->getRemoteEndpoint();
    try {
        if (handlerIt != _handlers.end())
            handlerIt->second(receiveMessage);
        else
            handleUnknownMessageType(receiveMessage);
    } catch (const std::exception &exception) {
        // A malformed packet must not take the server (and every player) down.
        std::cerr << "Ignoring malformed message: " << exception.what() << "\n";
    }
}

void RType::MessageParser::handlePlayerColor(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    Session session = getSenderSession(splitMessage);
    int sessionID = std::stoi(splitMessage[1]);

    if (session == nullptr || session->getEntity() == nullptr)
        return;
    session->setNextColor();
    char entityName[50];
    sprintf(entityName, "%sPlayer %d", session->getColor().c_str(), sessionID);
    session->getEntity()->setEntityName(entityName);
    char buffer[50];
    sprintf(buffer, "color %d %s\n", sessionID, session->getColor().c_str());
    _game->addMessageClients(-1, MessageType::PLAYER_COLOR, buffer);
}

void RType::MessageParser::handleDifficulty(const RType::Message &receiveMessage) {
    const std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");
    const std::optional<Difficulty> difficulty = parseDifficulty(splitMessage.at(2));

    // "difficulty <sessionID> <easy|normal|hard>": shared by everyone on the server.
    if (getSenderSession(splitMessage) != nullptr && difficulty.has_value())
        _game->setDifficulty(*difficulty);
}

void RType::MessageParser::handleTick(const RType::Message &receiveMessage) {
    const std::string message = receiveMessage.toString();
    std::vector<std::string> splitMessage = Split::split(message, " \n");

    // Ticks only keep the player's address fresh: updates are pushed every server tick.
    getSenderSession(splitMessage);
}

void RType::MessageParser::handlePlayerShoot(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector <std::string> splitMessage = Split::split(message, " \n");

    if (getSenderSession(splitMessage) == nullptr)
        return;
    _game->createBulletPlayerEntity(std::stoi(splitMessage[1]));
}

void RType::MessageParser::handleDisconnect(const RType::Message &receiveMessage) {
    std::string message = receiveMessage.toString();
    std::vector <std::string> splitMessage = Split::split(message, " \n");
    int sessionID = std::stoi(splitMessage.at(1));
    Session session = getSenderSession(splitMessage);

    if (session == nullptr)
        return;
    EntityPtr playerEntity = session->getEntity();
    if (playerEntity == nullptr)
        _game->sendTo(sessionID, MessageType::DISCONNECT, "disconnect\n");
    else {
        _game->sendTo(sessionID, MessageType::DISCONNECT, "disconnect " + playerEntity->getEntityName() + "\n");
        _game->addMessageClients(sessionID, MessageType::DISCONNECT, "disconnect " + playerEntity->getEntityName() + "\n");
        _game->getEntityManager().destroyEntity(playerEntity);
    }
    _sessions->deleteSession(sessionID);
    std::cout << "SessionID " + std::to_string(sessionID) + " disconnected!\n";
}
