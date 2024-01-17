/*
** EPITECH PROJECT, 2023
** RType
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

namespace RType {

    /**
     * @class AInputBox
     * @brief Abstract base class for input boxes in the RType game.
     * This class provides a base for implementing input boxes in the RType game.
     * It handles the basic functionality such as rendering, activation, and font settings.
     */
    class AInputBox {
    public:
        /**
         * @brief Constructor for AInputBox.
         * @param window Reference to the SFML RenderWindow.
         * @param x X-coordinate of the input box.
         * @param y Y-coordinate of the input box.
         * @param maxChars Maximum number of characters allowed in the input box.
         */
        explicit AInputBox(int x, int y, size_t maxChars)
                : _x(x), _y(y), _maxChars(maxChars) {
            _box->setSize(Vector2f(280, 40));
            _box->setPosition(Vector2f(x, y));
            _box->setOutlineColor(Color::RGB{200, 200, 200, 255});
            _box->setOutlineThickness(1);
            _box->setBackgroundColor(Color::Transparent);
            _textDisplay->setColor(Color::White);
            _textDisplay->setSize(20);
            _textDisplay->setPosition(Vector2f(x + 5, y + 5));
            _textDisplay->setFontPath("client/assets/ka1.ttf");
        }

        /**
         * @brief Destructor for AInputBox.
         */
        virtual ~AInputBox() = default;

        /**
         * @brief Update function for handling events.
         * This function is meant to be overridden by derived classes to handle specific
         * events related to the input box.
         * @param event SFML Event to be processed.
         */
        virtual void update(const sf::Event &event) = 0;

        /**
         * @brief Draw the input box on the SFML RenderWindow.
         */
        void draw() const {
            _box->draw();
            _textDisplay->draw();
        }

        /**
         * @brief Set the activation state of the input box.
         * @param active True to activate, false to deactivate.
         */
        void setActive(bool active) {
            _active = active;
            _box->setOutlineColor(active ? Color::Blue : Color::RGB{200, 200, 200, 255});
        }

        /**
         * @brief Check if the input box is currently active.
         * @return True if active, false otherwise.
         */
        [[nodiscard]] bool isActive() const {
            return _active;
        }

    protected:
        float _x; /**< X-coordinate of the input box. */
        float _y; /**< Y-coordinate of the input box. */
        size_t _maxChars; /**< Maximum number of characters allowed in the input box. */
        std::string _text; /**< Text content of the input box. */
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        TextComponent _textDisplay = _module->createText(""); /**< SFML Text displaying the text in the input box. */
        RectShape _box = _module->createRectShape(); /**< SFML RectangleShape representing the input box. */

    private:
        bool _active = false; /**< Activation state of the input box. */
    };
}
