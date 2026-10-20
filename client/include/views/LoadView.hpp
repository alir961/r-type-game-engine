/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include <cmath>
#include <utility>

#include "IView.hpp"
#include "../components/Button.hpp"
#include "../components/TitleBanner.hpp"

namespace RType {

    enum class ViewState;

    /**
     * @class LoadView
     * @brief Waits for the server to answer, and explains what to check when it doesn't.
     */
    class LoadView : public IView {
    private:
        static constexpr float SLOW_CONNECTION_SECONDS = 4.0F;

    public:
        /**
         * @brief Constructor for LoadView.
         * @param gameView The ClientViewport associated with the state.
         * @param client The client trying to connect.
         */
        LoadView(ClientViewport &gameView, UDPClientPtr client)
                : _viewport(gameView), _client(std::move(client)),
                  _status("Connecting to " + gameView.getServerAddress(), 34, Theme::Text, Theme::CENTER_X, 548.0F, Align::CENTER) {}

        void handleEvent(const sf::Event &event) override {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                goBack();
        }

        /**
         * @brief Go to the menu once connected.
         */
        void update() override {
            if (_client->getConnected())
                _viewport.setView(ViewState::MENU);
            _backButton.executeIfClicked([this] { goBack(); });
        }

        /**
         * @brief Draws the loading screen.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(std::vector<GraphicEntityPtr>) override {
            const float elapsed = _clock.getElapsedTime().asSeconds();

            _banner.draw();
            drawSpinner(elapsed);
            _status.draw();
            if (elapsed > SLOW_CONNECTION_SECONDS) {
                _slowTitle.draw();
                _slowServer.draw();
                _slowAddress.draw();
            }
            _backButton.draw();
        }

    private:
        ClientViewport &_viewport; /**< The associated ClientViewport. */
        UDPClientPtr _client;
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        TitleBanner _banner = TitleBanner("Join a game server");
        Label _status;
        Label _slowTitle = Label("Still waiting for an answer from the server...", 26, Theme::Warning, Theme::CENTER_X, 650.0F, Align::CENTER);
        Label _slowServer = Label("•  Is the server running?   ./build/out/server/r-type_server 4242", 24, Theme::TextDim,
                                  Theme::CENTER_X, 700.0F, Align::CENTER);
        Label _slowAddress = Label("•  Do the address and port match the ones the server was started with?", 24,
                                   Theme::TextDim, Theme::CENTER_X, 740.0F, Align::CENTER);
        Button _backButton = Button(Theme::CENTER_X - 230.0F, 830.0F, 460.0F, 72.0F, "Back");
        sf::Clock _clock;

        void goBack() {
            _logger->debug("Cancel connection from loading screen");
            _viewport.closeConnectionToServer();
            _viewport.setView(ViewState::LOGIN);
        }

        /**
         * @brief Eight dots turning in a circle, the brightest one leading.
         */
        void drawSpinner(float elapsed) {
            constexpr int DOTS = 8;
            const int head = static_cast<int>(elapsed * 10.0F) % DOTS;

            for (int i = 0; i < DOTS; i++) {
                const float angle = static_cast<float>(i) * 2.0F * static_cast<float>(M_PI) / DOTS;
                const int age = (head - i + DOTS) % DOTS;
                const auto alpha = static_cast<ColorComponent>(255 - age * 28);
                RectShape dot = _module->createRectShape();

                dot->setSize(Vector2f(12.0F, 12.0F));
                dot->setPosition(Vector2f(Theme::CENTER_X - 6.0F + std::cos(angle) * 34.0F, 468.0F - 6.0F + std::sin(angle) * 34.0F));
                dot->setBackgroundColor(Color::RGB{Theme::Accent.r, Theme::Accent.g, Theme::Accent.b, alpha});
                dot->draw();
            }
        }
    };
}
