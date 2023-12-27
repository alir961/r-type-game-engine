/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once
#include "IDraw.hpp"

namespace RType {
    class DeadState : public IDraw {
    public:
        void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>> graphicEntities) override {
        }
    };
}