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

void RType::GraphicalModule::drawTextPro(sf::RenderWindow &window, const std::string &colorName, unsigned int fontSize, float x, float y, const std::string &fontPath, const std::string &initialText) {
    sf::Text text;
    text.setCharacterSize(fontSize);
    text.setPosition(x, y);
    text.setString(initialText);
    sf::Color textColor = getColorFromString(colorName);
    text.setFillColor(textColor);
    if (!fontPath.empty()) {
        sf::Font font;
        font.loadFromFile(fontPath);
        text.setFont(font);
    }
    window.draw(text);
}

void RType::GraphicalModule::drawSpritePro(sf::RenderWindow &window, float spriteScaleX, float spriteScaleY, float x, float y, const std::string &texturePath) {
    sf::Sprite sprite;
    sprite.setPosition(x, y);
    sprite.setScale(spriteScaleX, spriteScaleY);
    if (!texturePath.empty()) {
        sf::Texture texture;
        texture.loadFromFile(texturePath);
        sprite.setTexture(texture);
    }
    window.draw(sprite);
}

void RType::GraphicalModule::drawRectPro(sf::RenderWindow &window, float rectSizeX, float rectSizeY, float x, float y, float outlineThickness, const std::string &lineColor, const std::string &fillColor, const std::string &texturePath) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(rectSizeX, rectSizeY));
    rect.setPosition(x, y);
    rect.setOutlineThickness(outlineThickness);
    rect.setOutlineColor(getColorFromString(lineColor));
    rect.setFillColor(getColorFromString(fillColor));
    if (!texturePath.empty()) {
        sf::Texture texture;
        texture.loadFromFile(texturePath);
        rect.setTexture(&texture);
    }
    window.draw(rect);
}

sf::Color RType::GraphicalModule::getColorFromString(const std::string &colorName) {
    std::string lowercaseColorName = colorName;
    std::transform(lowercaseColorName.begin(), lowercaseColorName.end(), lowercaseColorName.begin(), ::tolower);

    static const std::unordered_map<std::string, sf::Color> colorMap = {
            {"black", sf::Color::Black},
            {"white", sf::Color::White},
            {"red", sf::Color::Red},
            {"green", sf::Color::Green},
            {"blue", sf::Color::Blue},
            {"cyan", sf::Color::Cyan},
            {"magenta", sf::Color::Magenta},
            {"yellow", sf::Color::Yellow},
    };
    auto it = colorMap.find(lowercaseColorName);
    return (it != colorMap.end()) ? it->second : sf::Color::White;
}
