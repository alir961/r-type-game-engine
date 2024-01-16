/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "../components/CheckBox.hpp"
#include "../components/TextBox.hpp"
#include "IView.hpp"

namespace RType {

    /**
     * @brief Represents the options menu state in the game.
     *
     * This class provides functionality for handling user input, updating the state,
     * and drawing elements related to the options menu.
     */
    class OptionsView : public IView {
    public:
        /**
         * @brief Constructs the OptionsView.
         *
         * @param window Reference to the SFML render window.
         * @param gameView Reference to the ClientViewport.
         */
        OptionsView(ClientViewport &gameView, bool inGame = false)
            : _viewport(gameView), _inGame(inGame),
              _back(sf::Color::Cyan, 20, 700.0f, 350.0f, "Go Back") {}

        /**
         * @brief Handles user input for the options menu.
         */
        void handleInput() {
            _title.handleInput();
            _sound.handleInput();
            _soundVolume.handleInput();
            _mainMenu.handleInput();
            if (_inGame) _back.handleInput();
            _soundModuleBox.handleInput([this](std::string moduleName) { loadModule(moduleName); },
                                    [this](std::string moduleName) { unloadModule(moduleName);});
            _particleModuleBox.handleInput([this](std::string moduleName) { loadModule(moduleName); },
                                       [this](std::string moduleName) { unloadModule(moduleName);});
            _consoleModuleBox.handleInput([this](std::string moduleName) { loadModule(moduleName); },
                                    [this](std::string moduleName) { unloadModule(moduleName);});

            if (_module->isMouseClicked()) {
                if (_mainMenu.isActive()) {
                    std::cout << "Exit To Main Menu!" << std::endl;
                    _viewport.setView(ViewState::MENU);
                }
                if (_inGame && _back.isActive()) {
                    std::cout << "Back to Pause" << std::endl;
                    _viewport.setView(ViewState::PAUSE);
                }
            }
        }

        void loadModule(const std::string &moduleName) {
            const ModuleProviderPtr provider = ModuleProvider::getInstance();

            if (stringToModuleType(moduleName) == ModuleType::SOUND) provider->loadAndGetModule<RType::IModule>(RType::ModuleType::SOUND);
            if (stringToModuleType(moduleName) == ModuleType::PARTICLE) provider->loadAndGetModule<RType::IModule>(RType::ModuleType::PARTICLE);
            if (stringToModuleType(moduleName) == ModuleType::CONSOLE) provider->loadAndGetModule<RType::IModule>(RType::ModuleType::CONSOLE);
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
            _mainMenu.update();
            if (_inGame) _back.update();
        }

        /**
         * @brief Draws elements of the options menu on the screen.
         *
         * @param window Reference to the SFML render window.
         * @param entities A vector of shared pointers to graphic entities.
         */
        void draw(std::vector<GraphicEntityPtr>) override {
            _title.draw();
            _sound.draw();
            _soundVolume.draw();
            _mainMenu.draw();
            _consoleModuleBox.draw(_module);
            _particleModuleBox.draw(_module);
            _soundModuleBox.draw(_module);
            if (_inGame) _back.draw();
            handleInput();
        }

    private:
        TextBox _title = TextBox(sf::Color::Cyan, 30, WINDOW_WIDTH / 2.0f, 50.0f, "Options"); /**< TextBox for the title. */
        TextBox _sound = TextBox(sf::Color::Cyan, 20, 700.0f, 250.0f, "Sound"); /**< Sound of the ClientViewport. */
        TextBox _soundVolume = TextBox(sf::Color::Cyan, 20, 850.0f, 250.0f, "100"); /**< Game sound volume of the ClientViewport. */
        TextBox _mainMenu = TextBox(sf::Color::Cyan, 20, 700.0f, 300.0f, "Exit To Main Menu"); /**< TextBox for the menu. */
        TextBox _back; /**< TextBox to go back. */
        ClientViewport &_viewport; /**< Reference to the ClientViewport. */
        CheckBox _consoleModuleBox = CheckBox(WINDOW_WIDTH / 3.0f, WINDOW_HEIGHT / 3.0f + 50.0f, 50.0f, 50.0f, "Console");
        CheckBox _particleModuleBox = CheckBox(WINDOW_WIDTH / 3.0f + 200.0f, WINDOW_HEIGHT / 3.0f + 50.0f, 50.0f, 50.0f, "Particle");
        CheckBox _soundModuleBox = CheckBox(WINDOW_WIDTH / 3.0f + 400.0f, WINDOW_HEIGHT / 3.0f + 50.0f, 50.0f, 50.0f, "Sound");
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        bool _inGame;
    };
}
