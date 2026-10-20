#include "include/ClientViewport.hpp"

static void printProgramHeader() {
    std::cout << "\n\033[1;33;107m██████████████████████████████████████████████████████\033[0m\n";
    std::cout << "\033[1;33;107m█                       R-Type                       █\033[0m\n";
    std::cout << "\033[1;33;107m██████████████████████████████████████████████████████\033[0m\n\n";
}

static void startApplication() {
    RType::ClientViewport view;

    view.start();
}

int main() {
    printProgramHeader();
    startApplication();
}
