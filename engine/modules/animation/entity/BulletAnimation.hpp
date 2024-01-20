/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** BulletAnimation.hpp
*/

#pragma once

#include <array>
#include "../AAnimation.hpp"

namespace RType {

    const float BULLET_WIDTH = 14.0F;
    const float BULLET_HEIGHT = 14.0F;

    constexpr std::array<float, 4> FRAMES = {101.0F, 118.0F, 135.0F, 152.0F};

    class BulletAnimation : public AAnimation {
    public:
        BulletAnimation(float startX, float startY) : AAnimation(startX, startY, BULLET_WIDTH, BULLET_HEIGHT) {}

        RectFloat update() override {
            RectFloat frame = getCurrentFrame();

            if (_frameIndex == FRAMES.size() - 1)
                _frameIndex = 0;
            frame.left = FRAMES[_frameIndex];
            _frameIndex++;
            setCurrentFrame(frame);
            return getCurrentFrame();
        }

    private:
        int _frameIndex = 0;
    };
}
