/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#pragma once

#include "../AAnimation.hpp"

namespace RType {

    const float MONSTER_WIDTH = 33.0F;
    const float MONSTER_HEIGHT = 33.0F;

    class MonsterAnimation : public AAnimation {
    public:
        MonsterAnimation(float startX, float startY) : AAnimation(startX - MONSTER_WIDTH, startY, MONSTER_WIDTH, MONSTER_HEIGHT) {}

        RectFloat update() override {
            RectFloat frame = getCurrentFrame();
            if (frame.left >= MONSTER_WIDTH * 3)
                frame.left = 0;
            else frame.left += MONSTER_WIDTH;
            setCurrentFrame(frame);
            return frame;
        }
    };
}
