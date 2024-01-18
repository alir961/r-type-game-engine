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

    /**
     * @brief Alignment size for the Message structure.
     */
    constexpr std::size_t ALIGN_SIZE = 128;

    /**
     * @brief Size of the data array in the Message structure.
     */
    constexpr std::size_t DATA_SIZE = 256;

    /**
     * @brief Enumerates different types of network messages.
     */
    enum class MessageType {
        UNKNOWN = 0,
        NULLDATA,
        CONNECT,
        CONNECT_CALLBACK,
        DISCONNECT,
        CONFIRMATION,
        PLAYER_NAME,
        PLAYER_COLOR,
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_DOWN,
        MOVE_UP,
        SHOOT,
        BULLET_PLAYER,
        DEATH,
        MOVE_PLAYER_BULLET,
        TICK,
    };

#ifdef __linux__
#define ALIGN_ATTRIBUTE __attribute__((aligned(ALIGN_SIZE)))
#elif _WIN32
#define ALIGN_ATTRIBUTE __declspec(align(ALIGN_SIZE))
#endif

    /**
     * @brief Represents a network message with a specified type and data.
     */
    struct ALIGN_ATTRIBUTE Message {
        MessageType type = MessageType::UNKNOWN;
        std::array<char, DATA_SIZE> data = std::array<char, DATA_SIZE>();

        /**
         * @brief Serializes the message into a vector of bytes.
         * @return The serialized message as a vector of bytes.
         */
        [[nodiscard]] std::vector<std::byte> serialize() const;

        /**
         * @brief Converts the message to a string representation.
         * @return The message as a string.
         */
        [[nodiscard]] std::string toString() const;

        /**
        * @brief Deserializes a vector of bytes into a Message structure.
        * @param data The vector of bytes to deserialize.
        * @return The deserialized Message structure.
        */
        static Message deserialize(const std::vector<std::byte> &data);
    };

#undef ALIGN_ATTRIBUTE

    /**
     * @brief Builder class for constructing network messages.
     */
    class NetworkMessageBuilder {
    private:
        MessageType _type = MessageType::UNKNOWN;
        std::string _data;

    public:
        /**
         * @brief Default constructor for NetworkMessageBuilder.
         */
        NetworkMessageBuilder() = default;

        /**
         * @brief Parameterized constructor for NetworkMessageBuilder.
         * @param type The type of the message to be built.
         */
        explicit NetworkMessageBuilder(MessageType type) : _type(type) {};

        /**
         * @brief Sets the type of the message.
         * @param type The type of the message.
         * @return A reference to the updated NetworkMessageBuilder.
         */
        NetworkMessageBuilder &setType(MessageType type);

        /**
         * @brief Sets the data associated with the message.
         * @param data The data to be associated with the message.
         * @return A reference to the updated NetworkMessageBuilder.
         */
        NetworkMessageBuilder &setData(const std::string_view &data);

        /**
         * @brief Builds and returns the constructed message.
         * @return The built message.
         */
        [[nodiscard]] Message build() const;
    };

}