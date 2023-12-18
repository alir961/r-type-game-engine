/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <array>
#include <vector>
#include <cstring>
#include <string>

namespace RType {

    constexpr std::size_t ALIGN_SIZE = 128;
    constexpr std::size_t DATA_SIZE = 256;

    enum class MessageType {
        UNKNOWN = 0,
        CONNECT,
        CONNECT_CALLBACK,
        DISCONNECT,
        CONFIRMATION,
    };

    struct Message {
        MessageType type = MessageType::UNKNOWN;
        std::array<char, DATA_SIZE> data = std::array<char, DATA_SIZE>();

        [[nodiscard]] std::vector<std::byte> serialize() const;

        static Message deserialize(const std::vector<std::byte> &data);
    } __attribute__((aligned(ALIGN_SIZE)));

    class NetworkMessageBuilder {
    private:
        MessageType _type = MessageType::UNKNOWN;
        std::string _data;

    public:
        NetworkMessageBuilder() = default;

        explicit NetworkMessageBuilder(MessageType type) : _type(type) {};

        NetworkMessageBuilder &setType(MessageType type);

        NetworkMessageBuilder &setData(const std::string_view &data);

        [[nodiscard]] Message build() const;
    };

}
