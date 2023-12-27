/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once
#include "IDraw.hpp"

namespace RType {
    class GameState : public IDraw {
    public:
        void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>> graphicEntities) override {
            for (auto &entity: graphicEntities) {
                entity->draw(window);
            }
        }
    };
}
