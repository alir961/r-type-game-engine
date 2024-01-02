/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "GraphicalModule.hpp"

extern "C" {
RType::IModule *initializeGraphicalModule() {
    return new RType::GraphicalModule();
}

void destroy(RType::GraphicalModule *library) {
    delete library;
}
}

void RType::GraphicalModule::load() {
    std::cout << "Load Graphical Module\n";
}

void RType::GraphicalModule::unload() {
    std::cout << "Unload Graphical Module\n";
}

void RType::GraphicalModule::drawText(sf::RenderWindow &window, sf::Text text) {
    window.draw(text);
}

void RType::GraphicalModule::drawSprite(sf::RenderWindow &window, sf::Sprite sprite) {
    window.draw(sprite);
}

void RType::GraphicalModule::drawRect(sf::RenderWindow &window, sf::RectangleShape rect) {
    window.draw(rect);
}
