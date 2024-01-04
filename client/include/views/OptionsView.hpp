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
        using ModuleCallback = std::function<void(ModuleType)>;
        /**
         * @brief Constructs the OptionsView.
         *
         * @param window Reference to the SFML render window.
         * @param gameView Reference to the ClientViewport.
         */
        OptionsView(sf::RenderWindow &window, ClientViewport &gameView, IGraphicalModule *graphicalModule, ModuleProvider &provider)
            : _graphicalModule(graphicalModule), _viewport(gameView), _provider(provider),
              _title(window, sf::Color::Cyan, 30, window.getSize().x / 2.0f, 50.0f, "Options"),
              _sound(window, sf::Color::Cyan, 20, 500.0f, 250.0f, "Sound"),
              _soundVolume(window, sf::Color::Cyan, 20, 650.0f, 250.0f, "100"),
              _mainMenu(window, sf::Color::Cyan, 20, 500.0f, 300.0f, "Exit To Main Menu"),
              _consoleModuleBox(window, window.getSize().x / 4.0f, window.getSize().y / 3.0f + 50.0f, 50.0f, 50.0f, "Console"),
              _particleModuleBox(window, window.getSize().x / 4.0f + 200.0f, window.getSize().y / 3.0f + 50.0f, 50.0f, 50.0f, "Particle"),
              _soundModuleBox(window, window.getSize().x / 4.0f + 400.0f, window.getSize().y / 3.0f + 50.0f, 50.0f, 50.0f, "Sound") {}

        /**
         * @brief Handles user input for the options menu.
         */
        void handleInput() {
            _title.handleInput();
            _sound.handleInput();
            _soundVolume.handleInput();
            _mainMenu.handleInput();
            _soundModuleBox.handleInput([this](std::string moduleName) { loadModule(moduleName); },
                                    [this](std::string moduleName) { unloadModule(moduleName);});
            _particleModuleBox.handleInput([this](std::string moduleName) { loadModule(moduleName); },
                                       [this](std::string moduleName) { unloadModule(moduleName);});
            _consoleModuleBox.handleInput([this](std::string moduleName) { loadModule(moduleName); },
                                    [this](std::string moduleName) { unloadModule(moduleName);});

            if (isMouseClicked()) {
                if (_mainMenu.getActive()) {
                    std::cout << "Exit To Main Menu!" << std::endl;
                    _viewport.setView(ViewState::MENU);
                }
            }
        }

        void loadModule(std::string moduleName) {
            if (stringToModuleType(moduleName) == ModuleType::SOUND) _soundModule = _provider.loadAndGetModule<RType::IModule>(RType::ModuleType::SOUND);
            if (stringToModuleType(moduleName) == ModuleType::PARTICLE) _particleModule = _provider.loadAndGetModule<RType::IModule>(RType::ModuleType::PARTICLE);
            if (stringToModuleType(moduleName) == ModuleType::CONSOLE) _consoleModule = _provider.loadAndGetModule<RType::IModule>(RType::ModuleType::CONSOLE);
        }

        /**
         * @brief Unload the specified module.
         * @param moduleType The type of the module to unload.
         */
        void unloadModule(std::string moduleName) {
            if (stringToModuleType(moduleName) == ModuleType::SOUND) _provider.unloadModule(RType::ModuleType::SOUND);
            if (stringToModuleType(moduleName) == ModuleType::PARTICLE) _provider.unloadModule(RType::ModuleType::PARTICLE);
            if (stringToModuleType(moduleName) == ModuleType::CONSOLE) _provider.unloadModule(RType::ModuleType::CONSOLE);
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
        }

        /**
         * @brief Draws elements of the options menu on the screen.
         *
         * @param window Reference to the SFML render window.
         * @param entities A vector of shared pointers to graphic entities.
         */
        void draw(sf::RenderWindow &window, std::vector<GraphicEntityPtr>) override {
            _title.draw(_graphicalModule);
            _sound.draw(_graphicalModule);
            _soundVolume.draw(_graphicalModule);
            _mainMenu.draw(_graphicalModule);
            _consoleModuleBox.draw(_graphicalModule);
            _particleModuleBox.draw(_graphicalModule);
            _soundModuleBox.draw(_graphicalModule);
            handleInput();
        }

    private:
        TextBox _title; /**< TextBox for the title. */
        TextBox _sound; /**< Sound of the ClientViewport. */
        TextBox _soundVolume; /**< Game sound volume of the ClientViewport. */
        TextBox _mainMenu; /**< TextBox for the menu. */
        ClientViewport &_viewport; /**< Reference to the ClientViewport. */
        IGraphicalModule *_graphicalModule;
        CheckBox _consoleModuleBox;
        CheckBox _particleModuleBox;
        CheckBox _soundModuleBox;
        ModuleProvider &_provider;
        IModule *_soundModule;
        IModule *_particleModule;
        IModule *_consoleModule;

        /**
         * @brief Checks if the left mouse button is clicked.
         *
         * @return True if the left mouse button is clicked, false otherwise.
         */
        bool isMouseClicked() const {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
    };
}
