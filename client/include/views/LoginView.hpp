/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include <array>

#include "IView.hpp"
#include "../components/NumberInput.hpp"
#include "../components/TextInput.hpp"
#include "../components/Button.hpp"
#include "../components/TitleBanner.hpp"

namespace RType {

    enum class ViewState;

    /**
     * @class LoginView
     * @brief First screen: choose a username and the server to join.
     */
    class LoginView : public IView {
    private:
        static constexpr float PANEL_WIDTH = 720.0F;
        static constexpr float PANEL_X = Theme::CENTER_X - PANEL_WIDTH / 2.0F;
        static constexpr float PANEL_Y = 440.0F;
        static constexpr float FIELD_X = PANEL_X + 80.0F;

    public:
        /**
         * @brief Constructor for LoginView.
         * @param gameView The ClientViewport associated with the state.
         */
        explicit LoginView(ClientViewport &gameView) : _viewport(gameView) {
            _portBoxInput.setText("4242");
            _hostnameInput.setText("127.0.0.1");
            _usernameInput.setActive(true);
        }

        /**
         * @brief Typing in the fields, Tab to move between them, Enter to connect.
         */
        void handleEvent(const sf::Event &event) override {
            for (AInputBox *input: inputs())
                input->update(event);
            if (event.type != sf::Event::KeyPressed)
                return;
            if (event.key.code == sf::Keyboard::Tab)
                focusNextField(event.key.shift ? -1 : 1);
            else if (event.key.code == sf::Keyboard::Enter)
                submit();
        }

        /**
         * @brief Connect when the button is clicked.
         */
        void update() override {
            _loginButton.executeIfClicked([this] { submit(); });
        }

        /**
         * @brief Draws the login form.
         * @param entities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(std::vector<GraphicEntityPtr>) override {
            _banner.draw();
            _panel.draw();
            _usernameTitle.draw();
            _hostnameTitle.draw();
            _portBoxTitle.draw();
            _usernameInput.draw();
            _hostnameInput.draw();
            _portBoxInput.draw();
            _loginButton.draw();
            _errorText.draw();
            _keysHint.draw();
            _serverHint.draw();
        }

    private:
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        TitleBanner _banner = TitleBanner("Join a game server");
        Panel _panel = Panel(PANEL_X, PANEL_Y, PANEL_WIDTH, 470.0F);
        Label _usernameTitle = Label("Username", 26, Theme::TextDim, FIELD_X, PANEL_Y + 34.0F);
        Label _hostnameTitle = Label("Server address", 26, Theme::TextDim, FIELD_X, PANEL_Y + 150.0F);
        Label _portBoxTitle = Label("Port", 26, Theme::TextDim, FIELD_X + 420.0F, PANEL_Y + 150.0F);
        TextInput _usernameInput = TextInput(FIELD_X, PANEL_Y + 70.0F, 15); /**< Name shown above your ship. */
        TextInput _hostnameInput = TextInput(FIELD_X, PANEL_Y + 186.0F, 40, 400.0F); /**< Server hostname or IP. */
        NumberInput _portBoxInput = NumberInput(FIELD_X + 420.0F, PANEL_Y + 186.0F, 140.0F); /**< Server UDP port. */
        Button _loginButton = Button(FIELD_X, PANEL_Y + 290.0F, 560.0F, 72.0F, "Connect"); /**< Button for Log-in the game. */
        Label _errorText = Label("", 24, Theme::Danger, Theme::CENTER_X, PANEL_Y + 392.0F, Align::CENTER);
        Label _keysHint = Label("Tab  next field   •   Enter  connect", 22, Theme::TextDim, Theme::CENTER_X,
                                PANEL_Y + 428.0F, Align::CENTER);
        Label _serverHint = Label("No server running? Start one first:   ./build/out/server/r-type_server 4242",
                                  22, Theme::TextDim, Theme::CENTER_X, WINDOW_HEIGHT - 70.0F, Align::CENTER);

        std::array<AInputBox *, 3> inputs() {
            return {&_usernameInput, &_hostnameInput, &_portBoxInput};
        }

        void focusNextField(int direction) {
            auto fields = inputs();
            int current = 0;

            for (int i = 0; i < static_cast<int>(fields.size()); i++) {
                if (fields[i]->isActive())
                    current = i;
                fields[i]->setActive(false);
            }
            fields[(current + direction + static_cast<int>(fields.size())) % static_cast<int>(fields.size())]->setActive(true);
        }

        void submit() {
            const int port = _portBoxInput.getValue();

            if (_usernameInput.getValue().empty()) {
                _errorText.setText("Enter a username to show above your ship");
                return;
            }
            if (_hostnameInput.getValue().empty()) {
                _errorText.setText("Enter the server address (127.0.0.1 on this computer)");
                return;
            }
            if (port <= 0 || port > 65535) {
                _errorText.setText("The port must be a number between 1 and 65535");
                return;
            }
            try {
                _viewport.connectToServer(_hostnameInput.getValue(), port, _usernameInput.getValue());
            } catch (const std::exception &exception) {
                _logger->error(std::string("Unable to connect: ") + exception.what());
                _errorText.setText("Invalid server address: use an IP such as 127.0.0.1");
                return;
            }
            _viewport.setView(ViewState::LOADSCREEN);
        }
    };
}
