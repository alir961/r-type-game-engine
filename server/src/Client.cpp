/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#include "../include/Client.hpp"

void RType::Client::addMessage(const Message &message) {
    const std::scoped_lock lock(_queueMutex);

    _messageQueue.push_back(message);
}

RType::Message RType::Client::getLastMessage() {
    const std::lock_guard lock(_queueMutex);

    if (!_messageQueue.empty()) {
        Message message = _messageQueue.front();
        _messageQueue.erase(_messageQueue.begin());
        return message;
    }
    return NetworkMessageBuilder(MessageType::NULLDATA)
            .setData("")
            .build();
}

int RType::Client::getNextBulletID() {
    return (_lastBulletID++);
}
