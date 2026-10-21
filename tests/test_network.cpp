#include <gtest/gtest.h>

#include "exception/NetworkException.hpp"
#include "network/NetworkMessage.hpp"

using RType::Message;

TEST(NetworkMessage, RoundTripsThroughSerialize) {
    const Message sent = RType::NetworkMessageBuilder(RType::MessageType::CONNECT).setData("connect 800 600\n").build();
    const Message received = Message::deserialize(sent.serialize());

    EXPECT_EQ(received.type, RType::MessageType::CONNECT);
    EXPECT_EQ(received.toString(), "connect 800 600\n");
}

TEST(NetworkMessage, RejectsShortAndEmptyDatagrams) {
    EXPECT_THROW(Message::deserialize({}), RType::NetworkException);
    EXPECT_THROW(Message::deserialize(std::vector<std::byte>(1)), RType::NetworkException);
    EXPECT_THROW(Message::deserialize(std::vector<std::byte>(sizeof(Message) - 1)), RType::NetworkException);
}
