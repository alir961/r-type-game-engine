/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ConsoleOverlay.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Ui.hpp"
#include "engine/modules/console/IConsoleModule.hpp"

namespace RType {

    /**
     * @brief Draws the developer console over any screen and turns key presses into command lines.
     *
     * The command registry and history live in the console module; this only handles the screen side.
     */
    class ConsoleOverlay {
    private:
        static constexpr float HEIGHT = 440.0F;
        static constexpr std::size_t VISIBLE_LINES = 13;

        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        RectShape _background = _module->createRectShape();
        RectShape _separator = _module->createRectShape();
        std::string _input;
        std::size_t _recall = 0; /**< Position in the typed lines while browsing them with ↑ / ↓. */
        sf::Clock _caretClock;

    public:
        ConsoleOverlay() {
            _background->setPosition(Vector2f(0.0F, 0.0F));
            _background->setSize(Vector2f(WINDOW_WIDTH, HEIGHT));
            _background->setBackgroundColor(Color::RGB{4, 6, 18, 235});
            _separator->setPosition(Vector2f(0.0F, HEIGHT));
            _separator->setSize(Vector2f(WINDOW_WIDTH, 3.0F));
            _separator->setBackgroundColor(Theme::Accent);
        }

        static IConsoleModule *getConsole() {
            return ModuleProvider::getInstance()->get<IConsoleModule>(ModuleType::CONSOLE);
        }

        static bool isToggleKey(const sf::Event &event) {
            return event.type == sf::Event::KeyPressed &&
                   (event.key.code == sf::Keyboard::F2 || event.key.code == sf::Keyboard::Grave);
        }

        /**
         * @brief Feed a window event to the console.
         * @return True when the console used the event (the game and the menus must ignore it)
         */
        bool handleEvent(const sf::Event &event) {
            IConsoleModule *console = getConsole();

            if (console == nullptr)
                return false;
            if (isToggleKey(event)) {
                console->setOpen(!console->isOpen());
                _recall = console->getTypedLines().size();
                return true;
            }
            if (!console->isOpen())
                return false;
            if (event.type == sf::Event::TextEntered) {
                const auto character = event.text.unicode;

                // '`' and '²' open the console: don't type them.
                if (character >= 32 && character < 127 && character != '`' && _input.size() < 80)
                    _input += static_cast<char>(character);
                return true;
            }
            if (event.type == sf::Event::KeyPressed)
                handleKey(console, event.key.code);
            return event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased;
        }

        [[nodiscard]] static bool isOpen() {
            IConsoleModule *console = getConsole();

            return console != nullptr && console->isOpen();
        }

        void draw() {
            IConsoleModule *console = getConsole();

            if (console == nullptr || !console->isOpen())
                return;
            const auto &history = console->getHistory();
            const std::size_t first = history.size() > VISIBLE_LINES ? history.size() - VISIBLE_LINES : 0;
            const bool caret = static_cast<int>(_caretClock.getElapsedTime().asSeconds() * 2.0F) % 2 == 0;
            float y = 18.0F;

            _background->draw();
            _separator->draw();
            for (std::size_t i = first; i < history.size(); i++) {
                Label line(history[i], 24, history[i].starts_with("> ") ? Theme::Accent : Theme::Text, 28.0F, y);

                line.draw();
                y += 29.0F;
            }
            Label prompt("> " + _input + (caret ? "|" : ""), 26, Theme::Warning, 28.0F, HEIGHT - 46.0F);
            Label hint("F2 to close", 20, Theme::TextDim, WINDOW_WIDTH - 28.0F, HEIGHT - 42.0F, Align::RIGHT);

            prompt.draw();
            hint.draw();
        }

    private:
        void handleKey(IConsoleModule *console, sf::Keyboard::Key key) {
            const auto &typed = console->getTypedLines();

            switch (key) {
                case sf::Keyboard::Enter:
                    console->execute(_input);
                    _input.clear();
                    _recall = console->getTypedLines().size();
                    break;
                case sf::Keyboard::BackSpace:
                    if (!_input.empty())
                        _input.pop_back();
                    break;
                case sf::Keyboard::Escape:
                    console->setOpen(false);
                    break;
                case sf::Keyboard::Up:
                    if (_recall > 0)
                        _input = typed[--_recall];
                    break;
                case sf::Keyboard::Down:
                    _recall = std::min(_recall + 1, typed.size());
                    _input = _recall < typed.size() ? typed[_recall] : "";
                    break;
                default:
                    break;
            }
        }
    };

}
