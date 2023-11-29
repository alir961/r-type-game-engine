#include "engine/exception/ConfigurationException.hpp"
#include "include/Arguments.hpp"
#include <boost/asio.hpp>
#include <iostream>

namespace asio = boost::asio;

void handle_client(asio::ip::tcp::socket& socket) {
    asio::streambuf buffer;
    boost::system::error_code error;

    // Read data from the client
    asio::read_until(socket, buffer, '\n', error);
    if (error) {
        std::cerr << "Error reading data: " << error.message() << std::endl;
        return;
    }

    // Echo the data back to the client
    std::string message = asio::buffer_cast<const char*>(buffer.data());
    asio::write(socket, asio::buffer(message), error);
    if (error) {
        std::cerr << "Error writing data: " << error.message() << std::endl;
    }
}

static void startServer(const RType::Arguments &args) {
    const asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), args.getPort());
    asio::io_context context;
    asio::ip::tcp::acceptor acceptor(context, endpoint);

    std::cout << "Server started, listening on port " << args.getPort() << std::endl;

    while (true) {
        asio::ip::tcp::socket socket(context);

        acceptor.accept(socket);
        std::cout << "New connection from: " << socket.remote_endpoint() << std::endl;
        std::thread(handle_client, std::ref(socket)).detach();
    }
}

int main(int count, char **argv) {
    try {
        const auto arguments = RType::Arguments::parseArguments(count, argv);

        startServer(arguments);
        return 0;
    } catch (RType::ConfigurationException &) {
        std::cerr << "Usage: ./r-type_server <port>" << std::endl;
        return 1;
    }
}