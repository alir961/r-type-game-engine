/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ExplosionAnimation.hpp
*/

#pragma once

#include "../AAnimation.hpp"

namespace RType {

    constexpr float EXPLOSION_WIDTH = 48.0F;
    constexpr float EXPLOSION_HEIGHT = 48.0F;
    constexpr int EXPLOSION_FRAMES = 7;
    constexpr float EXPLOSION_FRAME_DURATION = 0.06F;

    /**
     * @brief One-shot blast played where an entity is destroyed.
     */
    class ExplosionAnimation : public AAnimation {
    public:
        ExplosionAnimation() : AAnimation(0.0F, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, EXPLOSION_FRAMES, EXPLOSION_FRAME_DURATION) {}
    };
}
