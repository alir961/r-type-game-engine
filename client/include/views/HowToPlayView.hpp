/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** HowToPlayView.hpp
*/

#pragma once

#include <string>
#include <vector>
#include "engine/modules/animation/IAnimationModule.hpp"
#include "../components/Button.hpp"
#include "IView.hpp"

namespace RType {

    /**
     * @brief Animated sprite shown next to an entry of the enemies guide.
     */
    class GuideIcon {
    private:
        ModuleProviderPtr _provider = ModuleProvider::getInstance();
        IGraphicalModule *_module = _provider->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        AnimationPtr _animation;
        SpriteComponent _sprite;
        float _time = 0.0F;

    public:
        /**
         * @param texturePath Sprite sheet of the entity
         * @param animationName Animation type, as used by the animation module
         * @param scale Display scale
         * @param center Where the icon is centered
         */
        GuideIcon(const std::string &texturePath, const std::string &animationName, float scale, const Vector2f &center)
                : _animation(_provider->loadAndGetModule<IAnimationModule>(ModuleType::ANIMATION)->createAnimation(animationName)),
                  _sprite(_module->createSprite(texturePath)) {
            const RectFloat frame = _animation->getCurrentFrame();

            _sprite->setRectangle(frame);
            _sprite->setScale(Vector2f(scale, scale));
            _sprite->setPosition(Vector2f(center.first - frame.width * scale / 2.0F, center.second - frame.height * scale / 2.0F));
        }

        void draw(float deltaTime) {
            _time += deltaTime;
            if (_time >= _animation->getFrameDuration()) {
                _sprite->setRectangle(_animation->update());
                _time = 0.0F;
            }
            _sprite->draw();
        }
    };

    /**
     * @class HowToPlayView
     * @brief Explains the controls, the enemies and how scoring works.
     */
    class HowToPlayView : public IView {
    private:
        static constexpr float LEFT_X = 120.0F;
        static constexpr float RIGHT_X = 1000.0F;
        static constexpr float PANEL_Y = 220.0F;
        static constexpr float ROWS_Y = 316.0F;
        static constexpr float CONTROL_STEP = 88.0F;
        static constexpr float ENEMY_STEP = 110.0F;

        struct Control {
            std::vector<std::string> keys;
            std::string action;
        };

        struct Enemy {
            std::string name;
            std::string description;
        };

    public:
        /**
         * @param gameView The ClientViewport associated with the state.
         * @param inGame True when opened from the pause menu (Back returns there).
         */
        explicit HowToPlayView(ClientViewport &gameView, bool inGame = false)
                : _viewport(gameView), _inGame(inGame),
                  _back(Theme::CENTER_X - 230.0F, 968.0F, 460.0F, 72.0F, inGame ? "Back to pause menu" : "Back to main menu") {
            const std::vector<std::pair<std::string, std::pair<std::string, float>>> icons = {
                    {"client/assets/sprites/monster.png", {"monster", 2.5F}},
                    {"client/assets/sprites/enemy_starship.png", {"starship", 2.5F}},
                    {"client/assets/sprites/mine.png", {"static", 0.7F}},
                    {"client/assets/sprites/enemy_bullet.png", {"bulletStarship", 2.5F}},
                    {"client/assets/sprites/player_bullet.png", {"bulletPlayer", 4.0F}},
            };

            for (size_t i = 0; i < icons.size(); i++) {
                const Vector2f center(RIGHT_X + 90.0F, ROWS_Y + 30.0F + static_cast<float>(i) * ENEMY_STEP);

                _icons.emplace_back(icons[i].first, icons[i].second.first, icons[i].second.second, center);
            }
        }

        /**
         * @brief Esc or Backspace goes back.
         */
        void handleEvent(const sf::Event &event) override {
            if (event.type == sf::Event::KeyPressed &&
                (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::BackSpace ||
                 event.key.code == sf::Keyboard::Enter))
                goBack();
        }

        void update() override {
            _back.executeIfClicked([this] { goBack(); });
        }

        void draw(std::vector<GraphicEntityPtr> entities) override {
            const float deltaTime = _clock.restart().asSeconds();

            if (_inGame)
                drawDimmedGame(entities);
            _title.draw();
            _subtitle.draw();
            drawControls();
            drawEnemies(deltaTime);
            _scoreTip.draw();
            _back.draw();
        }

    private:
        ClientViewport &_viewport;
        bool _inGame;
        Button _back;
        Label _title = Label("HOW TO PLAY", 64, Theme::Accent, Theme::CENTER_X, 56.0F, Align::CENTER);
        Label _subtitle = Label("Team up with the other pilots, dodge the fire and shoot everything that comes from the right.",
                                26, Theme::TextDim, Theme::CENTER_X, 148.0F, Align::CENTER);
        Panel _controlsPanel = Panel(LEFT_X, PANEL_Y, 820.0F, 680.0F);
        Panel _enemiesPanel = Panel(RIGHT_X, PANEL_Y, 800.0F, 680.0F);
        Label _controlsTitle = Label("CONTROLS", 30, Theme::Accent, LEFT_X + 40.0F, PANEL_Y + 26.0F);
        Label _enemiesTitle = Label("WHAT YOU WILL MEET", 30, Theme::Accent, RIGHT_X + 40.0F, PANEL_Y + 26.0F);
        Label _scoreTip = Label("Every hit adds its damage to your score.   You start with 4200 HP: the screen edges flash red when it runs low.",
                                22, Theme::TextDim, Theme::CENTER_X, 920.0F, Align::CENTER);
        std::vector<GuideIcon> _icons;
        sf::Clock _clock;

        const std::vector<Control> _controls = {
                {{"←", "↑", "↓", "→"}, "Move your ship"},
                {{"W", "A", "S", "D"}, "Move (Z Q S D on AZERTY)"},
                {{"SPACE"}, "Shoot (hold to keep firing)"},
                {{"C"}, "Change your ship color"},
                {{"ESC"}, "Pause and open the menu"},
                {{"H"}, "Show / hide the controls in game"},
        };

        const std::vector<Enemy> _enemies = {
                {"Bio-drone", "Zig-zags in from the right. 4 shots to kill. Never touch it."},
                {"Raider", "Fires a fireball every 2 seconds. Takes about 20 shots."},
                {"Space mine", "Indestructible: it absorbs your shots. Contact is fatal."},
                {"Fireball", "Raider shot: 300 damage. Dodge it, or shoot it to cancel it."},
                {"Your plasma shot", "150 damage per hit, and +150 to your score."},
        };

        void drawControls() {
            _controlsPanel.draw();
            _controlsTitle.draw();
            for (size_t i = 0; i < _controls.size(); i++) {
                const float y = ROWS_Y + static_cast<float>(i) * CONTROL_STEP;
                Label action(_controls[i].action, 28, Theme::Text, LEFT_X + 330.0F, y + KeyCap::HEIGHT / 2.0F);

                KeyCap::drawRow(_controls[i].keys, LEFT_X + 40.0F, y, 8.0F);
                action.setCenterY(true);
                action.draw();
            }
        }

        void drawEnemies(float deltaTime) {
            _enemiesPanel.draw();
            _enemiesTitle.draw();
            for (size_t i = 0; i < _enemies.size(); i++) {
                const float y = ROWS_Y + static_cast<float>(i) * ENEMY_STEP;
                Label name(_enemies[i].name, 28, Theme::Text, RIGHT_X + 190.0F, y);
                Label description(_enemies[i].description, 22, Theme::TextDim, RIGHT_X + 190.0F, y + 40.0F);

                _icons[i].draw(deltaTime);
                name.draw();
                description.draw();
            }
        }

        void goBack() {
            _logger->debug("Leave the controls guide");
            _viewport.setView(_inGame ? ViewState::PAUSE : ViewState::MENU);
        }
    };
}
