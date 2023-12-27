/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "../entities/AGraphicEntity.hpp"
#include <memory>

namespace RType {
    class IDraw {
    public:
        virtual void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>>) = 0;
        virtual ~IDraw() = default;
    };
}
