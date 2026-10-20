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
        _messageQueue.pop_front();
        return message;
    }
    return NetworkMessageBuilder(MessageType::NULLDATA)
            .setData("")
            .build();
}

std::deque<RType::Message> RType::Client::takeMessages() {
    const std::lock_guard lock(_queueMutex);
    std::deque<Message> messages;

    messages.swap(_messageQueue);
    return messages;
}

int RType::Client::getNextBulletID() {
    return (_lastBulletID++);
}
