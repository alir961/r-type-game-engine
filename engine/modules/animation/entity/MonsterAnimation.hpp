/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#pragma once

#include "../AAnimation.hpp"

namespace RType {

    constexpr float MONSTER_WIDTH = 33.0F;
    constexpr float MONSTER_HEIGHT = 33.0F;
    constexpr int MONSTER_FRAMES = 4;
    constexpr float MONSTER_FRAME_DURATION = 0.14F;

    /**
     * @brief Alien with waving tentacles and a blinking eye.
     */
    class MonsterAnimation : public AAnimation {
    public:
        MonsterAnimation() : AAnimation(0.0F, MONSTER_WIDTH, MONSTER_HEIGHT, MONSTER_FRAMES, MONSTER_FRAME_DURATION) {}
    };
}
