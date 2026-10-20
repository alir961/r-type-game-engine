/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "IView.hpp"
#include "../components/Background.hpp"
#include "../components/Ui.hpp"
#include "../entities/Explosion.hpp"
#include "../components/Effects.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>

namespace RType {

    /**
     * @class GameView
     * @brief The game itself: parallax background, entities, explosions and the HUD.
     */
    class GameView : public IView {
    private:
        static constexpr float CONTROLS_AUTO_HIDE_SECONDS = 10.0F;
        static constexpr float HEALTH_BAR_WIDTH = 420.0F;

    public:
        /**
         * @brief Constructor for GameView.
         * @param gameView The ClientViewport associated with the state.
         * @param explosions Explosions owned by the viewport, drawn over the entities.
         */
        GameView(ClientViewport &gameView, const std::vector<ExplosionPtr> &explosions)
                : _viewport(gameView), _explosions(explosions), _username(gameView.getUsername()) {
            _logger->info("Connected to server with user '" + _username + "'");
            _healthBackground->setPosition(Vector2f(48.0F, 86.0F));
            _healthBackground->setSize(Vector2f(HEALTH_BAR_WIDTH, 24.0F));
            _healthBackground->setBackgroundColor(Color::RGB{8, 10, 24, 255});
            _healthBackground->setOutlineColor(Theme::PanelBorder);
            _healthBackground->setOutlineThickness(2.0F);
            _healthFill->setPosition(Vector2f(48.0F, 86.0F));
        }

        /**
         * @brief Esc pauses, H shows or hides the controls reminder.
         */
        void handleEvent(const sf::Event &event) override {
            if (event.type != sf::Event::KeyPressed)
                return;
            if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P) {
                _logger->debug("Pause the game");
                _viewport.setView(ViewState::PAUSE);
            } else if (event.key.code == sf::Keyboard::H || event.key.code == sf::Keyboard::F1) {
                _showControls = !_showControls;
                _controlsToggled = true;
            }
        }

        void update() override {
            const GraphicEntityPtr player = getPlayerEntity();
            const EntityPtr &playerEntity = (player == nullptr) ? nullptr : player->getEntity();
            const float deltaTime = _clock.restart().asSeconds();

            _background.update(deltaTime);
            updateDifficultyBadge();
            _time += deltaTime;
            if (!_controlsToggled && _time > CONTROLS_AUTO_HIDE_SECONDS)
                _showControls = false;
            if (player != nullptr && playerEntity->getComponent<PlayerComponent>()) {
                _health = playerEntity->getComponent<HealthComponent>()->getHealth();
                _maxHealth = std::max(_maxHealth, _health);
                _healthRatio = static_cast<float>(_health) / static_cast<float>(std::max(1, _maxHealth));
                _playerNameText.setText(_username);
                _playerNameText.setColor(Theme::playerColor(playerEntity->getEntityName()));
                _healthText.setText(std::to_string(_health) + " / " + std::to_string(_maxHealth));
                _scoreText.setText(std::to_string(playerEntity->getComponent<PlayerComponent>()->getScore()));
            }
        }

        /**
         * @brief Draws the game and its HUD.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(std::vector<GraphicEntityPtr> graphicEntities) override {
            _background.draw();
            for (const auto &entity : graphicEntities)
                entity->draw();
            Particles::draw();
            for (const auto &explosion : _explosions)
                explosion->draw();
            if (getPlayerEntity() == nullptr) {
                _waitingText.draw();
                return;
            }
            if (_healthRatio < 0.3F)
                drawDangerVignette();
            drawHud();
            if (_showControls)
                drawControls();
            else
                _helpHint.draw();
        }

    private:
        ClientViewport &_viewport;
        const std::vector<ExplosionPtr> &_explosions;
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        Background _background = Background({"client/assets/background/1.png",
                                             "client/assets/background/2.png",
                                             "client/assets/background/3.png",
                                             "client/assets/background/4.png"},
                                            {0.2F, 0.5F, 1.0F, 2.0F});
        Panel _playerPanel = Panel(24.0F, 20.0F, 468.0F, 112.0F);
        Panel _scorePanel = Panel(WINDOW_WIDTH - 344.0F, 20.0F, 320.0F, 112.0F);
        Label _playerNameText = Label("", 30, Theme::Text, 48.0F, 34.0F);
        Label _healthLabel = Label("HP", 20, Theme::TextDim, HEALTH_BAR_WIDTH + 48.0F, 40.0F, Align::RIGHT);
        Label _healthText = Label("", 20, Theme::Text, 48.0F + HEALTH_BAR_WIDTH / 2.0F, 97.0F, Align::CENTER);
        Label _scoreLabel = Label("SCORE", 20, Theme::TextDim, WINDOW_WIDTH - 48.0F, 36.0F, Align::RIGHT);
        Label _scoreText = Label("0", 44, Theme::Accent, WINDOW_WIDTH - 48.0F, 62.0F, Align::RIGHT);
        Label _difficultyText = Label("", 22, Theme::Accent, WINDOW_WIDTH - 320.0F, 92.0F);
        Label _helpHint = Label("Esc  Pause     H  Show controls", 22, Theme::TextDim, 28.0F, WINDOW_HEIGHT - 48.0F);
        Label _waitingText = Label("Waiting for your ship...", 34, Theme::TextDim, Theme::CENTER_X, Theme::CENTER_Y, Align::CENTER);
        RectShape _healthBackground = _module->createRectShape();
        RectShape _healthFill = _module->createRectShape();
        sf::Clock _clock;
        std::string _username;
        float _time = 0.0F;
        bool _showControls = true;     /**< Controls reminder, shown when the game starts. */
        bool _controlsToggled = false; /**< Once the player toggles it, stop hiding it automatically. */
        int _health = 0;
        int _maxHealth = 0;
        float _healthRatio = 1.0F;

        void updateDifficultyBadge() {
            const std::string &difficulty = _viewport.getDifficulty();
            std::string text = difficulty;

            std::transform(text.begin(), text.end(), text.begin(), ::toupper);
            _difficultyText.setText(text);
            _difficultyText.setColor(difficulty == "easy" ? Theme::Success : difficulty == "hard" ? Theme::Danger : Theme::Accent);
        }

        void drawHud() {
            _playerPanel.draw();
            _scorePanel.draw();
            _playerNameText.draw();
            _healthLabel.draw();
            _healthFill->setSize(Vector2f(HEALTH_BAR_WIDTH * std::clamp(_healthRatio, 0.0F, 1.0F), 24.0F));
            _healthFill->setBackgroundColor(Theme::healthColor(_healthRatio));
            _healthBackground->draw();
            _healthFill->draw();
            _healthText.setCenterY(true);
            _healthText.draw();
            _scoreLabel.draw();
            _scoreText.draw();
            _difficultyText.draw();
        }

        /**
         * @brief Reminder of the keys at the bottom of the screen.
         */
        void drawControls() {
            const std::vector<std::pair<std::vector<std::string>, std::string>> controls = {
                    {{"←", "↑", "↓", "→"}, "Move"},
                    {{"SPACE"}, "Shoot"},
                    {{"C"}, "Ship color"},
                    {{"ESC"}, "Pause"},
                    {{"H"}, "Hide"},
            };
            const float y = WINDOW_HEIGHT - 112.0F;
            Panel panel(Theme::CENTER_X - 640.0F, y - 22.0F, 1280.0F, 98.0F, Color::RGB{14, 18, 44, 200});
            float x = Theme::CENTER_X - 600.0F;

            panel.draw();
            for (const auto &[keys, action]: controls) {
                Label label(action, 26, Theme::Text, 0.0F, y + KeyCap::HEIGHT / 2.0F);

                x += KeyCap::drawRow(keys, x, y, 6.0F) + 14.0F;
                label.setPosition(x, y + KeyCap::HEIGHT / 2.0F);
                label.setCenterY(true);
                x += label.getWidth() + 46.0F;
                label.draw();
            }
        }

        /**
         * @brief Pulsing red edges while health is critical.
         */
        void drawDangerVignette() {
            const float pulse = (std::sin(_time * 6.0F) + 1.0F) / 2.0F;
            const auto alpha = static_cast<ColorComponent>(40 + pulse * 70);
            const std::array<std::pair<Vector2f, Vector2f>, 4> edges = {{
                    {{0.0F, 0.0F}, {WINDOW_WIDTH, 18.0F}},
                    {{0.0F, WINDOW_HEIGHT - 18.0F}, {WINDOW_WIDTH, 18.0F}},
                    {{0.0F, 0.0F}, {18.0F, WINDOW_HEIGHT}},
                    {{WINDOW_WIDTH - 18.0F, 0.0F}, {18.0F, WINDOW_HEIGHT}},
            }};

            for (const auto &[position, size]: edges) {
                RectShape edge = _module->createRectShape();

                edge->setPosition(position);
                edge->setSize(size);
                edge->setBackgroundColor(Color::RGB{255, 40, 40, alpha});
                edge->draw();
            }
        }
    };
}
