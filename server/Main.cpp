#include "engine/exception/ConfigurationException.hpp"
#include "include/Arguments.hpp"
#include "include/UDPServer.hpp"
#include <iostream>

static int startServer(int count, char **args) {
    try {
        asio::io_context ioContext;
        const auto arguments = RType::Arguments::parseArguments(count, args);
        const UDP::endpoint endpoint(UDP::v4(), arguments.getPort());
        const auto server = RType::UDPServer(ioContext, endpoint);

        std::cout << "Starting server on " << endpoint.address() << ":" << endpoint.port() << "\n";
        ioContext.run();
        return 0;
    } catch (RType::ConfigurationException &) {
        std::cerr << "Usage: ./r-type_server <port>\n";
        return 1;
    }
}

int main(int count, char **args) {
    return startServer(count, args);
}