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
        OptionsView(sf::RenderWindow &window, ClientViewport &gameView, IGraphicalModule *graphicalModule, ModuleProvider &provider)
            : _graphicalModule(graphicalModule), _viewport(gameView), _provider(provider),
              title(window, sf::Color::Cyan, 30, window.getSize().x / 2.0f, 50.0f, "Options"),
              sound(window, sf::Color::Cyan, 20, 500.0f, 250.0f, "Sound"),
              soundVolume(window, sf::Color::Cyan, 20, 650.0f, 250.0f, "100"),
              mainMenu(window, sf::Color::Cyan, 20, 500.0f, 300.0f, "Exit To Main Menu"),
              consoleModule(window, window.getSize().x / 4.0f, window.getSize().y / 3.0f + 50.0f, 50.0f, 50.0f, "Console"),
              particleModule(window, window.getSize().x / 4.0f + 200.0f, window.getSize().y / 3.0f + 50.0f, 50.0f, 50.0f, "Particles"),
              soundModule(window, window.getSize().x / 4.0f + 400.0f, window.getSize().y / 3.0f + 50.0f, 50.0f, 50.0f, "Sound") {}

        /**
         * @brief Handles user input for the options menu.
         */
        void handleInput() {
            title.handleInput();
            sound.handleInput();
            soundVolume.handleInput();
            mainMenu.handleInput();
            consoleModule.handleInput(_provider);
            particleModule.handleInput(_provider);
            soundModule.handleInput(_provider);

            if (isMouseClicked()) {
                if (mainMenu.getActive()) {
                    std::cout << "Exit To Main Menu!" << std::endl;
                    _viewport.setView(ViewState::MENU);
                }
            }
        }

        /**
         * @brief Updates the options menu state.
         */
        void update() override {
            mainMenu.update();
        }

        /**
         * @brief Draws elements of the options menu on the screen.
         *
         * @param window Reference to the SFML render window.
         * @param entities A vector of shared pointers to graphic entities.
         */
        void draw(sf::RenderWindow &window, std::vector<GraphicEntityPtr>) override {
            title.draw(_graphicalModule);
            sound.draw(_graphicalModule);
            soundVolume.draw(_graphicalModule);
            mainMenu.draw(_graphicalModule);
            consoleModule.draw(_graphicalModule);
            particleModule.draw(_graphicalModule);
            soundModule.draw(_graphicalModule);
            handleInput();
        }

    private:
        TextBox title; /**< TextBox for the title. */
        TextBox sound; /**< Sound of the ClientViewport. */
        TextBox soundVolume; /**< Game sound volume of the ClientViewport. */
        TextBox mainMenu; /**< TextBox for the menu. */
        ClientViewport &_viewport; /**< Reference to the ClientViewport. */
        IGraphicalModule *_graphicalModule;
        CheckBox consoleModule;
        CheckBox particleModule;
        CheckBox soundModule;
        ModuleProvider &_provider;

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
