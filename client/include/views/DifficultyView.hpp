/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** DifficultyView.hpp
*/

#pragma once

#include <array>
#include <string>
#include <vector>
#include "../components/Button.hpp"
#include "IView.hpp"

namespace RType {

    /**
     * @brief One selectable difficulty: name, tagline and what it changes.
     */
    class DifficultyCard {
    private:
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        RectShape _body = _module->createRectShape();
        RectShape _accent = _module->createRectShape();
        Label _title;
        Label _tagline;
        std::vector<Label> _lines;
        Color::RGB _color;
        float _x;
        float _y;

    public:
        static constexpr float WIDTH = 460.0F;
        static constexpr float HEIGHT = 400.0F;

        DifficultyCard(float x, float y, const std::string &title, const std::string &tagline,
                       const std::vector<std::string> &lines, const Color::RGB &color)
                : _title(title, 52, color, x + WIDTH / 2.0F, y + 46.0F, Align::CENTER),
                  _tagline(tagline, 26, Theme::TextDim, x + WIDTH / 2.0F, y + 126.0F, Align::CENTER),
                  _color(color), _x(x), _y(y) {
            for (size_t i = 0; i < lines.size(); i++)
                _lines.emplace_back("•  " + lines[i], 24, Theme::Text, x + 40.0F, y + 200.0F + static_cast<float>(i) * 48.0F);
            _body->setPosition(Vector2f(x, y));
            _body->setSize(Vector2f(WIDTH, HEIGHT));
            _body->setOutlineThickness(3.0F);
            _accent->setPosition(Vector2f(x, y));
            _accent->setSize(Vector2f(WIDTH, 8.0F));
            _accent->setBackgroundColor(color);
        }

        [[nodiscard]] bool isHovered() const {
            const auto &[x, y] = _module->getMousePosition();

            return x >= _x && x <= _x + WIDTH && y >= _y && y <= _y + HEIGHT;
        }

        void draw(bool focused) {
            _body->setBackgroundColor(focused ? Color::RGB{30, 42, 86, 245} : Color::RGB{16, 22, 50, 225});
            _body->setOutlineColor(focused ? _color : Theme::PanelBorder);
            _body->draw();
            _accent->draw();
            _title.draw();
            _tagline.draw();
            for (auto &line: _lines)
                line.draw();
        }
    };

    /**
     * @class DifficultyView
     * @brief Pick Easy, Normal or Hard before starting a game.
     *
     * The server owns the rules, so the choice applies to every player connected to it.
     */
    class DifficultyView : public IView {
    private:
        static constexpr float CARDS_Y = 300.0F;
        static constexpr float GAP = 40.0F;
        static constexpr float FIRST_X = Theme::CENTER_X - (3.0F * DifficultyCard::WIDTH + 2.0F * GAP) / 2.0F;
        static constexpr std::array<const char *, 3> LEVELS = {"easy", "normal", "hard"};

    public:
        explicit DifficultyView(ClientViewport &gameView) : _viewport(gameView) {
            for (size_t i = 0; i < LEVELS.size(); i++) {
                if (gameView.getDifficulty() == LEVELS[i])
                    _focus = static_cast<int>(i);
            }
        }

        /**
         * @brief ←/→ to choose, Enter to start, Esc to go back.
         */
        void handleEvent(const sf::Event &event) override {
            if (event.type != sf::Event::KeyPressed)
                return;
            switch (event.key.code) {
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                case sf::Keyboard::Q:
                    _focus = (_focus + 2) % 3;
                    Audio::play("ui_move", 40.0F);
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                case sf::Keyboard::Tab:
                    _focus = (_focus + 1) % 3;
                    Audio::play("ui_move", 40.0F);
                    break;
                case sf::Keyboard::Enter:
                case sf::Keyboard::Space:
                    start(_focus);
                    break;
                case sf::Keyboard::Escape:
                case sf::Keyboard::BackSpace:
                    _viewport.setView(ViewState::MENU);
                    break;
                default:
                    break;
            }
        }

        void update() override {
            const Vector2f mouse = _module->getMousePosition();
            const bool mouseMoved = mouse != _lastMouse;

            _lastMouse = mouse;
            for (size_t i = 0; i < _cards.size(); i++) {
                if (!_cards[i].isHovered())
                    continue;
                if (mouseMoved)
                    _focus = static_cast<int>(i);
                if (_module->isMouseClicked())
                    start(static_cast<int>(i));
            }
            _back.executeIfClicked([this] { _viewport.setView(ViewState::MENU); });
        }

        void draw(std::vector<GraphicEntityPtr>) override {
            _title.draw();
            _subtitle.draw();
            for (size_t i = 0; i < _cards.size(); i++)
                _cards[i].draw(static_cast<int>(i) == _focus);
            _shared.draw();
            _keys.draw();
            _back.draw();
        }

    private:
        ClientViewport &_viewport;
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        Label _title = Label("CHOOSE YOUR DIFFICULTY", 64, Theme::Accent, Theme::CENTER_X, 90.0F, Align::CENTER);
        Label _subtitle = Label("You can change it every time you start a game.", 26, Theme::TextDim,
                                Theme::CENTER_X, 196.0F, Align::CENTER);
        std::array<DifficultyCard, 3> _cards = {
                DifficultyCard(FIRST_X, CARDS_Y, "EASY", "Learn the ropes",
                               {"Fewer enemies", "Weaker bio-drones and raiders", "Fireballs deal 150 damage"}, Theme::Success),
                DifficultyCard(FIRST_X + DifficultyCard::WIDTH + GAP, CARDS_Y, "NORMAL", "The intended challenge",
                               {"Steady waves", "Raiders fire every 2 seconds", "Fireballs deal 300 damage"}, Theme::Accent),
                DifficultyCard(FIRST_X + 2.0F * (DifficultyCard::WIDTH + GAP), CARDS_Y, "HARD", "Bring a friend",
                               {"Twice as many enemies", "Faster, tougher raiders", "Fireballs deal 450 damage"}, Theme::Danger),
        };
        Label _shared = Label("Online: the difficulty is shared by everyone on the server, the last pick applies to all.",
                              22, Theme::TextDim, Theme::CENTER_X, 750.0F, Align::CENTER);
        Label _keys = Label("←  →  to choose     Enter  to start     Esc  to go back", 22, Theme::TextDim,
                            Theme::CENTER_X, 790.0F, Align::CENTER);
        Button _back = Button(Theme::CENTER_X - 230.0F, 860.0F, 460.0F, 72.0F, "Back to main menu");
        Vector2f _lastMouse = _module->getMousePosition();
        int _focus = 1;

        void start(int level) {
            Audio::play("ui_select", 60.0F);
            _logger->debug(std::string("Start a game in ") + LEVELS[level]);
            _viewport.requestDifficulty(LEVELS[level]);
            _viewport.setView(ViewState::GAME);
        }
    };
}
