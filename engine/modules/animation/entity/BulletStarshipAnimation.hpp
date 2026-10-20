/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** BulletStarshipAnimation.hpp
*/

#pragma once

#include "../AAnimation.hpp"

namespace RType {

    constexpr float BULLET_STARSHIP_WIDTH = 32.0F;
    constexpr float BULLET_STARSHIP_HEIGHT = 28.0F;
    constexpr int BULLET_STARSHIP_FRAMES = 4;
    constexpr float BULLET_STARSHIP_FRAME_DURATION = 0.08F;

    /**
     * @brief Fireball shot fired by enemy starships.
     */
    class BulletStarshipAnimation : public AAnimation {
    public:
        BulletStarshipAnimation() : AAnimation(0.0F, BULLET_STARSHIP_WIDTH, BULLET_STARSHIP_HEIGHT, BULLET_STARSHIP_FRAMES, BULLET_STARSHIP_FRAME_DURATION) {}
    };
}
