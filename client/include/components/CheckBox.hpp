/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** CheckBox.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <cstring>

namespace RType {
    /**
     * @class CheckBox
     * @brief Represents a graphical checkbox with active and inactive states.
     */
    class CheckBox {
    public:
        /**
         * @brief Constructor for CheckBox.
         * @param window The SFML RenderWindow where the checkbox will be drawn.
         * @param position The position of the top-left corner of the checkbox.
         * @param size The size of the checkbox.
         * @param activeColor The color to fill the checkbox when active.
         * @param inactiveColor The color to fill the checkbox when inactive.
         * @param outlineColor The color of the outline of the checkbox.
         * @param outlineThickness The thickness of the outline of the checkbox.
         */
        CheckBox(sf::RenderWindow &window, float x, float y, float sizeX, float sizeY, const std::string boxName,
                 const sf::Color &activeColor = sf::Color::Cyan, const sf::Color &inactiveColor = sf::Color::Red,
                 const sf::Color &outlineColor = sf::Color::Black, float outlineThickness = 0.0f)
            : _window(window), _x(x), _y(y), _sizeX(sizeX), _sizeY(sizeY), activeColor(activeColor),
              inactiveColor(inactiveColor), outlineColor(outlineColor), outlineThickness(outlineThickness),
              isActive(false), _boxName(boxName) {
            rectangle.setPosition(_x, _y);
            rectangle.setSize(sf::Vector2f(_sizeX, _sizeY));
            rectangle.setFillColor(sf::Color::Magenta);
            font.loadFromFile("client/assets/ka1.ttf");
            _textSize = (_sizeX + _sizeY) / 5.0f;
            _boxNameText.setCharacterSize(static_cast<unsigned int>(_textSize));
            _boxNameText.setFont(font);
            _boxNameText.setString(boxName);
            _boxNameText.setFillColor(sf::Color::White);
            _boxNameText.setPosition(_x, _y + _sizeY);
            setAppearance();
        }

        /**
         * @brief Draws the checkbox on the associated SFML RenderWindow.
         */
        void draw(IGraphicalModule *graphicalModule) {
            graphicalModule->drawRect(_window, rectangle);
            graphicalModule->drawText(_window, _boxNameText);
        }

        /**
         * @brief Handles mouse click events on the checkbox.
         * Toggles the state of the checkbox and adjusts the appearance accordingly.
         * Also updates the opacity based on the state.
         */
        void handleInput(ModuleProvider &provider) {
            if (clickCoolDown.getElapsedTime().asSeconds() < clickCoolDownTime) return;
            sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(_window));
            std::transform(_boxName.begin(), _boxName.end(), _boxName.begin(), [](unsigned char c) {
                return std::tolower(c);
            });
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (rectangle.getGlobalBounds().contains(mousePosition)) {
                    isActive = !isActive;
                    setAppearance();
                    clickCoolDown.restart();
                    if (isActive) {
                        if (_boxName == "sound") _soundModule = provider.loadAndGetModule<RType::IModule>(RType::ModuleType::SOUND);
                        if (_boxName == "particles") _particleModule = provider.loadAndGetModule<RType::IModule>(RType::ModuleType::PARTICLE);
                        if (_boxName == "console") _consoleModule = provider.loadAndGetModule<RType::IModule>(RType::ModuleType::CONSOLE);
                        std::cout << _boxName << " Box set active!" << std::endl;
                    } else {
                        if (_boxName == "sound") provider.unloadModule(RType::ModuleType::SOUND);
                        if (_boxName == "particles") provider.unloadModule(RType::ModuleType::PARTICLE);
                        if (_boxName == "console") provider.unloadModule(RType::ModuleType::CONSOLE);
                        std::cout << _boxName << " Box set inactive!" << std::endl;
                    }
                }
            }
        }

    private:
        sf::RenderWindow &_window; /**< The SFML RenderWindow where the checkbox will be drawn. */
        float _x, _y;
        float _sizeX, _sizeY;
        sf::Color activeColor; /**< The color to fill the checkbox when active. */
        sf::Color inactiveColor; /**< The color to fill the checkbox when inactive. */
        sf::Color outlineColor; /**< The color of the outline of the checkbox. */
        float outlineThickness; /**< The thickness of the outline of the checkbox. */
        bool isActive; /**< The current state of the checkbox (active or inactive). */
        sf::RectangleShape rectangle; /**< The SFML RectangleShape representing the checkbox. */
        sf::Clock clickCoolDown;
        const float clickCoolDownTime = 0.1;
        std::string _boxName;
        sf::Font font;
        sf::Text _boxNameText;
        float _textSize;
        IModule *_soundModule;
        IModule *_particleModule;
        IModule *_consoleModule;

        /**
         * @brief Sets the appearance of the checkbox based on its current state.
         */
        void setAppearance() {
            if (isActive) {
                rectangle.setFillColor(activeColor);
            } else {
                rectangle.setFillColor(inactiveColor);
            }
            rectangle.setOutlineColor(outlineColor);
            rectangle.setOutlineThickness(outlineThickness);
        }
    };
}
