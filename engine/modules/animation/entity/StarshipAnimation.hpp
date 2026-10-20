/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** StarshipAnimation.hpp
*/

#pragma once

#include "../AAnimation.hpp"

namespace RType {

    constexpr float STARSHIP_WIDTH = 32.0F;
    constexpr float STARSHIP_HEIGHT = 22.0F;
    constexpr int STARSHIP_FRAMES = 4;
    constexpr float STARSHIP_FRAME_DURATION = 0.08F;

    /**
     * @brief Enemy fighter with flickering twin engines.
     */
    class StarshipAnimation : public AAnimation {
    public:
        StarshipAnimation() : AAnimation(0.0F, STARSHIP_WIDTH, STARSHIP_HEIGHT, STARSHIP_FRAMES, STARSHIP_FRAME_DURATION) {}
    };
}
