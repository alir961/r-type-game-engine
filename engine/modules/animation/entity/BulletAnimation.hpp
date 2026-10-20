/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** BulletAnimation.hpp
*/

#pragma once

#include "../AAnimation.hpp"

namespace RType {

    constexpr float BULLET_WIDTH = 14.0F;
    constexpr float BULLET_HEIGHT = 14.0F;
    constexpr int BULLET_FRAMES = 4;
    constexpr float BULLET_FRAME_DURATION = 0.06F;

    /**
     * @brief Pulsing plasma shot fired by players.
     */
    class BulletAnimation : public AAnimation {
    public:
        BulletAnimation() : AAnimation(0.0F, BULLET_WIDTH, BULLET_HEIGHT, BULLET_FRAMES, BULLET_FRAME_DURATION) {}
    };
}
