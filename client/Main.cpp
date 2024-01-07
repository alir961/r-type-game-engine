#include "include/ClientViewport.hpp"
#include <engine/Logger.hpp>
#include <engine/network/UDPAdapter.hpp>

int main() {
    RType::ClientViewport view;

    logInformation("Hello, World for client!");
    view.start();
}
