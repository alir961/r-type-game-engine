#include <engine/Logger.hpp>
#include "include/GameView.hpp"

int main() {
    RType::GameView view;

    logInformation("Hello, World for client!");
    view.start();
}