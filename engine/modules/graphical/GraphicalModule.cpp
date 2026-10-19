/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "GraphicalModule.hpp"
#include "Text.hpp"
#include "Rectangle.hpp"
#include "Sprite.hpp"

extern "C" {
RType::IModule *initializeGraphicalModule() {
    return new RType::GraphicalModule();
}

void destroy(RType::GraphicalModule *library) {
    delete library;
}
}

void RType::GraphicalModule::openWindow(uint32_t width, uint32_t height, std::string title) {
    if (_window != nullptr && _window->isOpen())
        _window->close();
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title);
    _window->setFramerateLimit(WINDOW_FPS);
}

RType::TextComponent RType::GraphicalModule::createText(const std::string &text) {
    return std::make_shared<RType::Text>(_window, text);
}

void RType::GraphicalModule::load() {}

void RType::GraphicalModule::unload() {}

void RType::GraphicalModule::drawSprite(sf::Sprite sprite) {
    //window.draw(sprite);
}

void RType::GraphicalModule::drawRect(sf::RectangleShape rect) {
    //window.draw(rect);
}

void RType::GraphicalModule::drawTextPro(const std::string &colorName, unsigned int fontSize, float x, float y,
                                         const std::string &initialText) {
    sf::Text text;
    text.setCharacterSize(fontSize);
    text.setPosition(x, y);
    text.setString(initialText);
    sf::Color textColor = getColorFromString(colorName);
    text.setFillColor(textColor);
    std::string fontPath = "client/assets/ka1.ttf";
    if (!fontPath.empty()) {
        sf::Font font;
        font.loadFromFile(fontPath);
        text.setFont(font);
    }
    _window->draw(text);
}

void RType::GraphicalModule::drawSpritePro(float spriteScaleX, float spriteScaleY, float x, float y,
                                           const std::string &texturePath) {
    sf::Sprite sprite;
    sprite.setPosition(x, y);
    sprite.setScale(spriteScaleX, spriteScaleY);
    if (!texturePath.empty()) {
        sf::Texture texture;
        texture.loadFromFile(texturePath);
        sprite.setTexture(texture);
    }
    _window->draw(sprite);
}

void RType::GraphicalModule::drawRectPro(float rectSizeX, float rectSizeY, float x, float y, float outlineThickness,
                                         const std::string &lineColor,
                                         const std::string &fillColor, const std::string &texturePath) {
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
    _window->draw(rect);
}

sf::Color RType::GraphicalModule::getColorFromString(const std::string &colorName) {
    std::string lowercaseColorName = colorName;
    std::transform(lowercaseColorName.begin(), lowercaseColorName.end(), lowercaseColorName.begin(), ::tolower);

    static const std::unordered_map<std::string, sf::Color> colorMap = {
            {"black",   sf::Color::Black},
            {"white",   sf::Color::White},
            {"red",     sf::Color::Red},
            {"green",   sf::Color::Green},
            {"blue",    sf::Color::Blue},
            {"cyan",    sf::Color::Cyan},
            {"magenta", sf::Color::Magenta},
            {"yellow",  sf::Color::Yellow},
            {"orange",  sf::Color(255, 165, 0)},
            {"gray",    sf::Color(128, 128, 128)},
    };

    auto it = colorMap.find(lowercaseColorName);
    return (it != colorMap.end()) ? it->second : sf::Color::White;
}

void RType::GraphicalModule::close() {
    _window->close();
}

bool RType::GraphicalModule::isOpen() {
    return (_window && _window->isOpen());
}

void RType::GraphicalModule::clear() {
    _window->clear();
}

void RType::GraphicalModule::display() {
    _window->display();
}

bool RType::GraphicalModule::pollEvent(sf::Event &event) {
    //return _window->pollEvent(reinterpret_cast<sf::Event &>(event));
    return _window->pollEvent(event);
}

RType::Vector2f RType::GraphicalModule::getMousePosition() {
    const sf::Vector2i position = sf::Mouse::getPosition();

    return {position.x % WINDOW_WIDTH, position.y % WINDOW_HEIGHT};
}

bool RType::GraphicalModule::isMouseClicked() {
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

RType::RectShape RType::GraphicalModule::createRectShape() {
    return std::make_shared<RType::Rectangle>(_window);
}

RType::SpriteComponent RType::GraphicalModule::createSprite(const std::string &texturePath) {
    return std::make_shared<RType::Sprite>(_window, texturePath);
}
