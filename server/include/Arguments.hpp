/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "engine/tools/NumberUtilities.hpp"
#include "engine/exception/ServerException.hpp"
#include "game/Difficulty.hpp"
#include <span>
#include <utility>

namespace RType {

    class Arguments {
    private:
        uint16_t _port;
        Difficulty _difficulty;

    public:
        explicit Arguments(uint16_t port, Difficulty difficulty = Difficulty::NORMAL) : _port(port), _difficulty(difficulty) {};

        [[nodiscard]] uint16_t getPort() const {
            return _port;
        };

        [[nodiscard]] Difficulty getDifficulty() const {
            return _difficulty;
        };


        static Arguments parseArguments(int count, char **argv) {
            if (count != 2 && count != 3)
                throw RType::ConfigurationException("Missing port number");
            try {
                const auto args = std::span(argv, count);
                const auto port = static_cast<uint16_t>(parseToUnsignedLong(args[1]));
                const auto difficulty = count == 3 ? parseDifficulty(args[2]) : Difficulty::NORMAL;

                if (!difficulty.has_value())
                    throw RType::ConfigurationException("Unknown difficulty");
                return Arguments(port, *difficulty);
            } catch (ServerException &) {
                throw RType::ConfigurationException("Missing port number");
            }
        }

    };

}
