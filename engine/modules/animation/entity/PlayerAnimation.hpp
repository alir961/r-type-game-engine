/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#pragma once

#include "../AAnimation.hpp"

namespace RType {

    constexpr float PLAYER_WIDTH = 33.0F;
    constexpr float PLAYER_HEIGHT = 15.0F;
    constexpr int PLAYER_FRAMES = 4;
    constexpr float PLAYER_FRAME_DURATION = 0.08F;

    /**
     * @brief Ship with a flickering engine flame; one row per player color.
     */
    class PlayerAnimation : public AAnimation {
    public:
        explicit PlayerAnimation(float row) : AAnimation(row * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_FRAMES, PLAYER_FRAME_DURATION) {}
    };
}
