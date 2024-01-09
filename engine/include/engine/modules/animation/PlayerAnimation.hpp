/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#pragma once

#include "Animation.hpp"

namespace RType {

    const float PLAYER_WIDTH = 33.0F;
    const float PLAYER_HEIGHT = 15.0F;

    class PlayerAnimation : public Animation {
    public:
        PlayerAnimation(float startX, float startY) : Animation(startX - PLAYER_WIDTH, startY, PLAYER_WIDTH, PLAYER_HEIGHT) {}
        sf::FloatRect update() override {
            sf::FloatRect frame = getCurrentFrame();

            if (frame.left >= PLAYER_WIDTH * 4)
                frame.left = 0;
            else
                frame.left += PLAYER_WIDTH;
            setCurrentFrame(frame);
            return getCurrentFrame();
        }
    };
}
