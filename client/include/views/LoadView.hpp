/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include <utility>

#include "IView.hpp"
#include "../components/TextBox.hpp"
#include "../components/NumberInput.hpp"
#include "../components/TextInput.hpp"
#include "../components/Button.hpp"

namespace RType {

    enum class ViewState;

    /**
     * @class LoginView
     * @brief Represents a login state with input box for user interaction.
     */
    class LoadView : public IView {
    public:
        /**
         * @brief Constructor for MenuView.
         * @param window The SFML RenderWindow.
         * @param gameView The ClientViewport associated with the state.
         */
        LoadView(ClientViewport &gameView, UDPClientPtr client) : _viewport(gameView), _client(std::move(client)) {}

        /**
         * @brief Handles user input for the menu.
         */
        void handleInput() {
            _quitBox.handleInput();
            if (_client->getConnected())
                _viewport.setView(ViewState::MENU);
            if (_quitBox.isActive()) {
                std::cout << "Quit Game!\n";
                _viewport.closeConnectionToServer();
                _module->close();
                std::exit(0);
            }
        }

        /**
         * @brief Updates the menu state.
         */
        void update() override {
            _quitBox.update();
        }

        /**
         * @brief Draws the menu on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the menu.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(std::vector<GraphicEntityPtr>) override {
            _loadingText.draw();
            _quitBox.draw();
            handleInput();
        }

    private:
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        TextBox _quitBox = TextBox(Color::Cyan, 20, 900.0f, 350.0f, "Quit"); /**< TextBox for quitting the game. */
        TextBox _loadingText = TextBox(Color::Magenta, 20, 250.0f, 300.0f, "Loading... if problem persist check server status and the port you provided and re launch"); /**< TextBox for Port of the game server. */
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        UDPClientPtr _client;
    };
}
