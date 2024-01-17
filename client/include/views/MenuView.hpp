/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "engine/modules/graphical/IGraphicalModule.hpp"
#include "../components/ClickableText.hpp"
#include "IView.hpp"

namespace RType {

    /**
     * @class MenuView
     * @brief Represents a state with a menu for user interaction.
     */
    class MenuView : public IView {
    public:
        /**
         * @brief Constructor for MenuView.
         * @param window The SFML RenderWindow.
         * @param gameView The ClientViewport associated with the state.
         */
        explicit MenuView(ClientViewport &gameView) : _viewport(gameView) {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            _titleBox.handleInput();
            _startBox.handleInput();
            _optionsBox.handleInput();
            _quitBox.handleInput();

            if (_module->isMouseClicked()) {
                if (_startBox.isClicked()) {
                    std::cout << "Start Game!\n";
                    _viewport.setView(ViewState::GAME);
                } else if (_optionsBox.isClicked()) {
                    std::cout << "Options Selected!\n";
                    _viewport.setView(ViewState::OPTIONS);
                } else if (_quitBox.isClicked()) {
                    std::cout << "Quit Game!\n";
                    _viewport.closeConnectionToServer();
                    _module->close();
                }
            }
        }

        /**
         * @brief Updates the menu state.
         */
        void update() override {
            _startBox.update();
            _optionsBox.update();
            _quitBox.update();
        }

        /**
         * @brief Draws the menu on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the menu.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(std::vector<GraphicEntityPtr>) override {
            _titleBox.draw();
            _startBox.draw();
            _optionsBox.draw();
            _quitBox.draw();
            handleInput();
        }

    private:
        ClickableText _titleBox = ClickableText(Color::Cyan, 30, WINDOW_WIDTH / 2.0f, 50.0f, "R Type"); /**< ClickableText for the game title. */
        ClickableText _startBox = ClickableText(Color::Cyan, 20, 100.0f, 200.0f, "Start"); /**< ClickableText for starting the game. */
        ClickableText _optionsBox = ClickableText(Color::Cyan, 20, 100.0f, 250.0f, "Options"); /**< ClickableText for accessing options. */
        ClickableText _quitBox = ClickableText(Color::Cyan, 20, 100.0f, 300.0f, "Quit"); /**< ClickableText for quitting the game. */
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
    };
}
