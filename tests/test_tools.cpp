#include <gtest/gtest.h>

#include <thread>

#include "exception/ServerException.hpp"
#include "tools/NumberUtilities.hpp"
#include "tools/SafeQueue.hpp"
#include "tools/Split.hpp"

using RType::Split;

TEST(Split, SplitsOnAnySeparator) {
    EXPECT_EQ(Split::split("a b,c", " ,"), (std::vector<std::string>{"a", "b", "c"}));
}

TEST(Split, CollapsesConsecutiveAndEdgeSeparators) {
    EXPECT_EQ(Split::split("  player   42 ", " "), (std::vector<std::string>{"player", "42"}));
}

TEST(Split, EmptyAndSeparatorOnlyInputs) {
    EXPECT_TRUE(Split::split("", " ").empty());
    EXPECT_TRUE(Split::split("   ", " ").empty());
}

TEST(NumberUtilities, ParsesSignedAndUnsigned) {
    EXPECT_EQ(RType::parseToLong("-42"), -42);
    EXPECT_EQ(RType::parseToUnsignedLong("4242"), 4242U);
}

TEST(NumberUtilities, RejectsNonNumbers) {
    EXPECT_THROW(RType::parseToLong("port"), RType::ServerException);
    EXPECT_THROW(RType::parseToUnsignedLong(""), RType::ServerException);
}

TEST(SafeQueue, IsFifo) {
    RType::SafeQueue<int> queue;
    queue.push(1);
    queue.push(2);
    int value = 0;
    ASSERT_TRUE(queue.safePop(value));
    EXPECT_EQ(value, 1);
    ASSERT_TRUE(queue.safePop(value));
    EXPECT_EQ(value, 2);
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_FALSE(queue.safePop(value));
}

TEST(SafeQueue, PopWaitsForProducerThread) {
    RType::SafeQueue<std::string> queue;
    std::thread producer([&queue] {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        queue.push("packet");
    });
    EXPECT_EQ(queue.pop(), "packet");
    producer.join();
}
