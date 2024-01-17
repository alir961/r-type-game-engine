#include "include/ClientViewport.hpp"

int main() {
    std::cout << "\e[1;97m------------------------------------------------------\e[0m\n";
    std::cout << "\e[1;97m|\t\t\tR-Type\t\t\t     |\e[0m\n";
    std::cout << "\e[1;97m------------------------------------------------------\e[0m\n";
    RType::ClientViewport view;

    view.start();
}
