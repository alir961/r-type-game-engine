#include "engine/exception/ConfigurationException.hpp"
#include "include/Arguments.hpp"
#include "include/UDPServer.hpp"
#include <iostream>
#include <stdlib.h>

static int startServer(int count, char **args) {
    try {
        const auto arguments = RType::Arguments::parseArguments(count, args);
        const auto server = RType::UDPServer(arguments.getPort());

        return 0;
    } catch (RType::ConfigurationException &) {
        std::cerr << "Usage: ./r-type_server <port>\n";
        return 1;
    }
}

int main(int count, char **args) {
    srand(time(nullptr));

    return startServer(count, args);
}