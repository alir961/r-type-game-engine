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
#include <utility>

namespace RType {

    class Arguments {
    private:
        std::string _hostname;
        uint16_t _port;

    public:
        explicit Arguments(std::string hostname, uint16_t port) : _hostname(std::move(hostname)), _port(port) {};

        [[nodiscard]] uint16_t getPort() const {
            return _port;
        };

        [[nodiscard]] std::string getHostname() const {
            return _hostname;
        };

        static Arguments parseArguments(int count, char **argv) {
            if (count != 3)
                throw RType::ConfigurationException("Missing port number or hostname");
            try {
                const auto args = std::span(argv, count);
                const auto hostname = std::string(args[1]);
                const auto port = static_cast<uint16_t>(parseToUnsignedLong(args[2]));

                return Arguments(hostname, port);
            } catch (ServerException &) {
                throw RType::ConfigurationException("Missing port number or hostname");
            }
        }

    };

}
