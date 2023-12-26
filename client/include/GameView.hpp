/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once

#include "entities/GraphicEntity.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <memory>
#include <vector>

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
    std::vector<std::shared_ptr<AGraphicEntity>> graphicEntities;

    void draw();
    void updateEntities(float deltaTime);
    void handleInput(std::shared_ptr<AGraphicEntity> &entity);

public:
    explicit GameView();
    ~GameView() = default;

    void start(std::shared_ptr<AGraphicEntity> entity); // put graphical entity by parameters to test entity move with keyboard input : function is handleInput
    void setView(ViewState state);
    void addGraphicEntity(std::shared_ptr<AGraphicEntity> entity);
};
