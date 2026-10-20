/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "../components/Button.hpp"
#include "../components/CheckBox.hpp"
#include "IView.hpp"

namespace RType {

    /**
     * @brief Represents the options menu state in the game.
     *
     * Lets the player load or unload engine modules (shared libraries) while the game runs.
     */
    class OptionsView : public IView {
    private:
        static constexpr float ROW_X = Theme::CENTER_X - CheckBox::WIDTH / 2.0F;

    public:
        /**
         * @brief Constructs the OptionsView.
         *
         * @param gameView Reference to the ClientViewport.
         * @param inGame True when opened from the pause menu (Back returns there).
         */
        OptionsView(ClientViewport &gameView, bool inGame = false)
            : _viewport(gameView), _inGame(inGame),
              _back(Theme::CENTER_X - 230.0F, 720.0F, 460.0F, 72.0F, inGame ? "Back to pause menu" : "Back to main menu") {}

        /**
         * @brief Esc or Backspace goes back.
         */
        void handleEvent(const sf::Event &event) override {
            if (event.type == sf::Event::KeyPressed &&
                (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::BackSpace))
                goBack();
        }

        /**
         * @brief Handles clicks on the module switches and on the back button.
         */
        void handleInput() {
            _soundModuleBox.handleInput([this](std::string moduleName) { loadModule(moduleName); },
                                    [this](std::string moduleName) { unloadModule(moduleName);});
            _particleModuleBox.handleInput([this](std::string moduleName) { loadModule(moduleName); },
                                       [this](std::string moduleName) { unloadModule(moduleName);});
            _consoleModuleBox.handleInput([this](std::string moduleName) { loadModule(moduleName); },
                                    [this](std::string moduleName) { unloadModule(moduleName);});
            _back.executeIfClicked([this] { goBack(); });
        }

        void loadModule(const std::string &moduleName) {
            const ModuleProviderPtr provider = ModuleProvider::getInstance();

            // Each switch has a visible or audible effect right away, so the player knows it worked.
            if (stringToModuleType(moduleName) == ModuleType::SOUND) {
                provider->loadAndGetModule<RType::IModule>(RType::ModuleType::SOUND);
                Audio::playMusic("music", _viewport.musicVolume());
                Audio::play("ui_select", 60.0F);
            }
            if (stringToModuleType(moduleName) == ModuleType::PARTICLE) {
                provider->loadAndGetModule<RType::IModule>(RType::ModuleType::PARTICLE);
                Particles::explosion({ROW_X + CheckBox::WIDTH - 60.0F, 468.0F}, 1.2F);
            }
            if (stringToModuleType(moduleName) == ModuleType::CONSOLE) {
                provider->loadAndGetModule<RType::IModule>(RType::ModuleType::CONSOLE);
                _viewport.setupConsole();
            }
        }

        /**
         * @brief Unload the specified module.
         * @param moduleType The type of the module to unload.
         */
        void unloadModule(const std::string &moduleName) {
            const ModuleProviderPtr provider = ModuleProvider::getInstance();

            if (stringToModuleType(moduleName) == ModuleType::SOUND) provider->unloadModule(RType::ModuleType::SOUND);
            if (stringToModuleType(moduleName) == ModuleType::PARTICLE) provider->unloadModule(RType::ModuleType::PARTICLE);
            if (stringToModuleType(moduleName) == ModuleType::CONSOLE) provider->unloadModule(RType::ModuleType::CONSOLE);
        }

        /**
         * @brief convert string to RType::ModuleType.
         * @param str The string we want to convert to RType::ModuleType.
         */
        ModuleType stringToModuleType(const std::string &str) {
            std::string lowercaseStr = str;
            std::transform(lowercaseStr.begin(), lowercaseStr.end(), lowercaseStr.begin(), ::tolower);

            static const std::unordered_map<std::string, ModuleType> moduleTypeMap = {
                    {"sound", ModuleType::SOUND},
                    {"console", ModuleType::CONSOLE},
                    {"particle", ModuleType::PARTICLE},
            };

            auto it = moduleTypeMap.find(lowercaseStr);
            if (it != moduleTypeMap.end()) {
                return it->second;
            } else {
                return ModuleType::UNKNOWN;
            }
        }

        /**
         * @brief Updates the options menu state.
         */
        void update() override {
            handleInput();
        }

        /**
         * @brief Draws elements of the options menu on the screen.
         *
         * @param entities A vector of shared pointers to graphic entities.
         */
        void draw(std::vector<GraphicEntityPtr> entities) override {
            if (_inGame)
                drawDimmedGame(entities);
            _title.draw();
            _subtitle.draw();
            _consoleModuleBox.draw();
            _particleModuleBox.draw();
            _soundModuleBox.draw();
            _back.draw();
            // In game, drawDimmedGame already drew them.
            if (!_inGame)
                Particles::draw();
        }

    private:
        ClientViewport &_viewport; /**< Reference to the ClientViewport. */
        bool _inGame;
        ModuleProviderPtr _provider = ModuleProvider::getInstance();
        Label _title = Label("OPTIONS", 64, Theme::Accent, Theme::CENTER_X, 120.0F, Align::CENTER);
        Label _subtitle = Label("Engine modules are shared libraries loaded at runtime: switch them on or off while you play.",
                                24, Theme::TextDim, Theme::CENTER_X, 220.0F, Align::CENTER);
        CheckBox _consoleModuleBox = CheckBox(ROW_X, 300.0F, "Console", "Developer console: press F2 (libconsole_module.so)",
                                              _provider->get<IModule>(ModuleType::CONSOLE) != nullptr);
        CheckBox _particleModuleBox = CheckBox(ROW_X, 420.0F, "Particle", "Explosions, sparks and engine trails in game (libparticle_module.so)",
                                               _provider->get<IModule>(ModuleType::PARTICLE) != nullptr);
        CheckBox _soundModuleBox = CheckBox(ROW_X, 540.0F, "Sound", "Music and sound effects (libsound_module.so)",
                                            _provider->get<IModule>(ModuleType::SOUND) != nullptr);
        Button _back; /**< Returns to the main menu or to the pause menu. */
        IGraphicalModule *_module = _provider->get<IGraphicalModule>(ModuleType::GRAPHICAL);

        void goBack() {
            _logger->debug(_inGame ? "Go to pause menu from options" : "Go to main menu from options");
            _viewport.setView(_inGame ? ViewState::PAUSE : ViewState::MENU);
        }
    };
}
