#include "include/ClientViewport.hpp"

static void printProgramHeader() {
    std::cout << "\n\e[1;33;107m██████████████████████████████████████████████████████\e[0m\n";
    std::cout << "\e[1;33;107m█                       R-Type                       █\e[0m\n";
    std::cout << "\e[1;33;107m██████████████████████████████████████████████████████\e[0m\n\n";
}

static void startApplication() {
    RType::ClientViewport view;

    view.start();
}

int main() {
    printProgramHeader();
    startApplication();
}
