#include "include/GameView.hpp"
#include <engine/Logger.hpp>

int main() {
    RType::GameView view;

    logInformation("Hello, World for client!");
    view.start();
}