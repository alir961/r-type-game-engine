/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** STATICAnimation.hpp
*/

#pragma once

#include "../AAnimation.hpp"

namespace RType {

    constexpr float STATIC_WIDTH = 122.0F;
    constexpr float STATIC_HEIGHT = 122.0F;
    constexpr int STATIC_FRAMES = 8;
    constexpr float STATIC_FRAME_DURATION = 0.1F;

    /**
     * @brief Slowly spinning space mine with a pulsing warning light.
     */
    class StaticAnimation : public AAnimation {
    public:
        StaticAnimation() : AAnimation(0.0F, STATIC_WIDTH, STATIC_HEIGHT, STATIC_FRAMES, STATIC_FRAME_DURATION) {}
    };
}
