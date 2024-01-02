/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "engine/tools/NumberUtilities.hpp"
#include "engine/exception/ServerException.hpp"
#include <span>

namespace RType {

    class Arguments {
    private:
        u_int16_t _port;

    public:
        explicit Arguments(u_int16_t port) : _port(port) {};

        [[nodiscard]] u_int16_t getPort() const {
            return _port;
        };

        static Arguments parseArguments(int count, char **argv) {
            if (count != 2)
                throw RType::ConfigurationException("Missing port number");
            try {
                const auto args = std::span(argv, count);
                const auto port = static_cast<u_int16_t>(parseToUnsignedLong(args[1]));

                return Arguments(port);
            } catch (ServerException &) {
                throw RType::ConfigurationException("Missing port number");
            }
        }

    };

}
