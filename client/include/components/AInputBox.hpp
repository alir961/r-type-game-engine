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
#include "Ui.hpp"

namespace RType {

    /**
     * @brief Abstract base class for text input boxes.
     */
    class AInputBox {
    public:
        static constexpr float HEIGHT = 58.0F;

        /**
         * @brief Constructor for AInputBox.
         * @param x X-coordinate of the input box.
         * @param y Y-coordinate of the input box.
         * @param maxChars Maximum number of characters allowed in the input box.
         * @param width Width of the input box.
         */
        explicit AInputBox(int x, int y, size_t maxChars, float width = 560.0F)
                : _x(x), _y(y), _maxChars(maxChars) {
            _box->setSize(Vector2f(width, HEIGHT));
            _box->setPosition(Vector2f(x, y));
            _box->setOutlineThickness(2);
            _box->setBackgroundColor(Color::RGB{8, 12, 30, 230});
            _textDisplay->setColor(Theme::Text);
            _textDisplay->setSize(30);
            _textDisplay->setPosition(Vector2f(x + 16, y + 10));
            _textDisplay->setFontPath(Theme::FONT);
            setActive(false);
        }

        virtual ~AInputBox() = default;

        /**
         * @brief Handle one window event: focus on click, then typing and backspace.
         * @param event The SFML event.
         */
        void update(const sf::Event &event) {
            checkIfActive(event);
            appendInput(event);
        }

        /**
         * @brief Draw the input box, with a blinking caret while focused.
         */
        void draw() const {
            const bool caret = _active && static_cast<int>(_caretClock.getElapsedTime().asSeconds() * 2.0F) % 2 == 0;

            _textDisplay->setText(_text + (caret ? "|" : ""));
            _box->draw();
            _textDisplay->draw();
        }

        /**
         * @brief Set the activation state of the input box.
         * @param active The new activation state.
         */
        void setActive(bool active) {
            _active = active;
            _caretClock.restart();
            _box->setOutlineColor(active ? Theme::Accent : Theme::PanelBorder);
        }

        /**
         * @brief Check if the input box is active.
         * @return True if the input box is active, false otherwise.
         */
        [[nodiscard]] bool isActive() const {
            return _active;
        }

        virtual void setText(std::string value) = 0;

    protected:
        float _x; /**< X-coordinate of the input box. */
        float _y; /**< Y-coordinate of the input box. */
        size_t _maxChars; /**< Maximum number of characters allowed in the input box. */
        std::string _text = ""; /**< Text content of the input box. */
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        TextComponent _textDisplay = _module->createText(""); /**< Text displaying the content of the input box. */
        RectShape _box = _module->createRectShape(); /**< Rectangle drawn behind the text. */
        sf::Clock _caretClock; /**< Drives the caret blinking. */

        void checkIfActive(const sf::Event &event) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                const Vector2f mousePosition = _module->getMousePosition();

                setActive(_box->getGlobalBounds().contains(mousePosition));
            }
        }

        void appendInput(const sf::Event &event) {
            if (!isActive() || event.type != sf::Event::TextEntered || event.text.unicode >= 128)
                return;
            auto inputChar = static_cast<char>(event.text.unicode);

            if (inputChar == '\b') {
                if (!_text.empty())
                    _text.pop_back();
            } else if (isValidInput(inputChar) && _text.size() < _maxChars) {
                _text += inputChar;
            }
        }

    private:
        bool _active = false; /**< Activation state of the input box. */

        /**
         * @brief Check if the input character is valid for this input box.
         * @param character The input character.
         * @return True if the character is valid, false otherwise.
         */
        [[nodiscard]] virtual bool isValidInput(char character) = 0;
    };
}
