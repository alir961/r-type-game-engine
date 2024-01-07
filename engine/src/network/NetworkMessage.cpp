/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include <iostream>
#include "network/NetworkMessage.hpp"
#include "exception/NetworkException.hpp"

namespace RType {

    std::vector<std::byte> Message::serialize() const {
        return std::vector<std::byte>(reinterpret_cast<const std::byte *>(this),
                                      reinterpret_cast<const std::byte *>(this + 1));
    }

    Message Message::deserialize(const std::vector<std::byte> &data) {
        Message msg{};

        std::memcpy(&msg, data.data(), sizeof(Message));
        return msg;
    }

    std::string Message::toString() const {
        std::string result;

        for (const auto &item: data) {
            if (item == 0) break;
            result += item;
        }
        return result;
    }

    NetworkMessageBuilder &NetworkMessageBuilder::setType(MessageType type) {
        _type = type;

        return (*this);
    }

    NetworkMessageBuilder &NetworkMessageBuilder::setData(const std::string_view &data) {
        if (data.length() > DATA_SIZE)
            throw NetworkException("NetworkMessage data cannot be longer than " + std::to_string(DATA_SIZE) + "bytes");
        _data = data;

        return (*this);
    }

    Message NetworkMessageBuilder::build() const {
        auto array = std::array<char, DATA_SIZE>();

        if (_type == MessageType::UNKNOWN)
            throw NetworkException("NetworkMessage type is unknown");
        if (_data.length() > DATA_SIZE)
            throw NetworkException("NetworkMessage data cannot be longer than " + std::to_string(DATA_SIZE) + "bytes");
        _data.copy(array.data(), array.size());
        return Message(_type, array);
    }

}