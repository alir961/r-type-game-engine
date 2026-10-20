/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include <algorithm>
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
    // Keep the game in a fixed width x height world, but size the window to fit the screen.
    const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const float fit = std::min({1.0F, desktop.width * 0.9F / width, desktop.height * 0.9F / height});
    const sf::VideoMode mode(static_cast<unsigned>(width * fit), static_cast<unsigned>(height * fit));

    _window = std::make_shared<sf::RenderWindow>(mode, title, sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    _window->setView(sf::View(sf::FloatRect(0.0F, 0.0F, static_cast<float>(width), static_cast<float>(height))));
    _window->setPosition(sf::Vector2i(static_cast<int>(desktop.width - mode.width) / 2, static_cast<int>(desktop.height - mode.height) / 2));
    _window->setFramerateLimit(WINDOW_FPS);
    _window->setKeyRepeatEnabled(false);
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

void RType::GraphicalModule::drawSquares(const std::vector<ColoredSquare> &squares) {
    sf::VertexArray vertices(sf::Quads, squares.size() * 4);

    for (std::size_t i = 0; i < squares.size(); i++) {
        const auto &[center, size, color] = squares[i];
        const float half = size / 2.0F;
        const sf::Color sfColor(color.r, color.g, color.b, color.a);

        vertices[i * 4] = sf::Vertex(sf::Vector2f(center.first - half, center.second - half), sfColor);
        vertices[i * 4 + 1] = sf::Vertex(sf::Vector2f(center.first + half, center.second - half), sfColor);
        vertices[i * 4 + 2] = sf::Vertex(sf::Vector2f(center.first + half, center.second + half), sfColor);
        vertices[i * 4 + 3] = sf::Vertex(sf::Vector2f(center.first - half, center.second + half), sfColor);
    }
    _window->draw(vertices, sf::RenderStates(sf::BlendAdd));
}

void RType::GraphicalModule::close() {
    _window->close();
}

bool RType::GraphicalModule::isOpen() {
    return (_window && _window->isOpen());
}

void RType::GraphicalModule::clear() {
    _mouseWasPressed = _mousePressed;
    _mousePressed = _window->hasFocus() && sf::Mouse::isButtonPressed(sf::Mouse::Left);
    _window->clear(sf::Color(6, 8, 22));
}

void RType::GraphicalModule::display() {
    _window->display();
}

bool RType::GraphicalModule::pollEvent(sf::Event &event) {
    if (!_window->pollEvent(event))
        return false;
    if (event.type == sf::Event::Resized) {
        // Letterbox: keep the world's aspect ratio whatever the window shape.
        sf::View view = _window->getView();
        const float windowRatio = static_cast<float>(event.size.width) / static_cast<float>(event.size.height);
        const float worldRatio = view.getSize().x / view.getSize().y;

        if (windowRatio > worldRatio)
            view.setViewport(sf::FloatRect((1.0F - worldRatio / windowRatio) / 2.0F, 0.0F, worldRatio / windowRatio, 1.0F));
        else
            view.setViewport(sf::FloatRect(0.0F, (1.0F - windowRatio / worldRatio) / 2.0F, 1.0F, windowRatio / worldRatio));
        _window->setView(view);
    }
    return true;
}

RType::Vector2f RType::GraphicalModule::getMousePosition() {
    const sf::Vector2f position = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));

    return {position.x, position.y};
}

bool RType::GraphicalModule::isMouseClicked() {
    // Only the frame where the button goes down counts as a click, so a click
    // that switches view doesn't also press whatever sits under the cursor next.
    return _mousePressed && !_mouseWasPressed;
}

bool RType::GraphicalModule::hasFocus() {
    return _window->hasFocus();
}

RType::RectShape RType::GraphicalModule::createRectShape() {
    return std::make_shared<RType::Rectangle>(_window);
}

RType::SpriteComponent RType::GraphicalModule::createSprite(const std::string &texturePath) {
    return std::make_shared<RType::Sprite>(_window, texturePath);
}
