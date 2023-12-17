/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once

#include "entities/GraphicBullet.hpp"
#include "entities/GraphicMonster.hpp"
#include "entities/GraphicStarship.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <memory>
#include <vector>

namespace RType {

    constexpr uint32_t WINDOW_WIDTH = 1920;
    constexpr uint32_t WINDOW_HEIGHT = 1920;

    enum class ViewState {
        MENU = 0,
        OPTIONS = 1,
        GAME = 2,
        PAUSE = 3,
        DEAD = 4
    };

    class GameView {
    private:
        sf::RenderWindow _window;
        ViewState _viewState;
        sf::Clock animationClock;
        std::vector<std::shared_ptr<IGraphicEntity>> graphicEntities;

        void draw();
        void updateEntities(float deltaTime);

    public:
        explicit GameView();
        ~GameView() = default;

        void start();
        void setView(ViewState state);
        void addGraphicEntity(std::shared_ptr<IGraphicEntity> entity);
    };
}// namespace RType
