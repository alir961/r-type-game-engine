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
        using ModuleCallback = std::function<void(std::string)>;

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
        CheckBox(float x, float y, float sizeX, float sizeY, const std::string boxName,
                 const sf::Color &activeColor = sf::Color::Cyan, const sf::Color &inactiveColor = sf::Color::Red,
                 const sf::Color &outlineColor = sf::Color::Black, float outlineThickness = 0.0f)
                : _x(x), _y(y), _sizeX(sizeX), _sizeY(sizeY), _activeColor(activeColor),
                  _inactiveColor(inactiveColor), _outlineColor(outlineColor), _outlineThickness(outlineThickness),
                  _boxName(boxName) {
            _rectangle.setPosition(_x, _y);
            _rectangle.setSize(sf::Vector2f(_sizeX, _sizeY));
            _rectangle.setFillColor(sf::Color::Magenta);
            _font.loadFromFile("client/assets/ka1.ttf");
            _textSize = (_sizeX + _sizeY) / 5.0f;
            _boxNameText.setCharacterSize(static_cast<unsigned int>(_textSize));
            _boxNameText.setFont(_font);
            _boxNameText.setString(boxName);
            _boxNameText.setFillColor(sf::Color::White);
            _boxNameText.setPosition(_x, _y + _sizeY);
            setAppearance();
        }

        /**
         * @brief Draws the checkbox on the associated SFML RenderWindow.
         */
        void draw(IGraphicalModule *graphicalModule) {
            graphicalModule->drawRect(_rectangle);
            //graphicalModule->drawText(_window, _boxNameText);
        }

        /**
         * @brief Handles mouse click events on the checkbox.
         * Toggles the state of the checkbox and adjusts the appearance accordingly.
         * Also updates the opacity based on the state.
         */
        void handleInput(const ModuleCallback &loadCallback, const ModuleCallback &unloadCallback) {
            if (_clickCoolDown.getElapsedTime().asSeconds() < _clickCoolDownTime) return;
            const auto &[x, y] = _module->getMousePosition();

            std::transform(_boxName.begin(), _boxName.end(), _boxName.begin(), [](unsigned char c) {
                return std::tolower(c);
            });
            if (!_module->isMouseClicked())
                return;
            if (_rectangle.getGlobalBounds().contains(x, y)) {
                _active = !_active;
                setAppearance();
                _clickCoolDown.restart();
                if (_active) {
                    loadCallback(_boxName);
                    std::cout << _boxName << " Box set active!\n";
                } else {
                    unloadCallback(_boxName);
                    std::cout << _boxName << " Box set inactive!\n";
                }
            }
        }

    private:
        float _x;
        float _y;
        float _sizeX;
        float _sizeY;
        sf::Color _activeColor; /**< The color to fill the checkbox when active. */
        sf::Color _inactiveColor; /**< The color to fill the checkbox when inactive. */
        sf::Color _outlineColor; /**< The color of the outline of the checkbox. */
        float _outlineThickness; /**< The thickness of the outline of the checkbox. */
        bool _active = false; /**< The current state of the checkbox (active or inactive). */
        sf::RectangleShape _rectangle; /**< The SFML RectangleShape representing the checkbox. */
        sf::Clock _clickCoolDown;
        float _clickCoolDownTime = 0.1F;
        std::string _boxName;
        sf::Font _font;
        sf::Text _boxNameText;
        float _textSize;
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);

        /**
         * @brief Sets the appearance of the checkbox based on its current state.
         */
        void setAppearance() {
            if (_active) {
                _rectangle.setFillColor(_activeColor);
            } else {
                _rectangle.setFillColor(_inactiveColor);
            }
            _rectangle.setOutlineColor(_outlineColor);
            _rectangle.setOutlineThickness(_outlineThickness);
        }
    };
}
