/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace RType {

    enum class ViewState {
        MENU = 0,
        OPTIONS = 1,
        GAME = 2,
        PAUSE = 3,
        DEAD = 4
    };

    class GameView {
    private:
        sf::RenderWindow _window = sf::RenderWindow(sf::VideoMode(1920, 1080), "R-Type");
        ViewState _viewState = ViewState::MENU;

    protected:
        void draw();

    public:
        explicit GameView() = default;

        ~GameView() = default;

        /**
         * Launch the GUI and wait until close
         */
        void start();

        /**
         * Update current view
         *
         * @param state view to display
         */
        void setView(ViewState state);
    };

}
