/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** BulletStarshipAnimation.hpp
*/

#pragma once

#include <array>
#include "../AAnimation.hpp"

namespace RType {

    const float BULLET_STARSHIP_WIDTH = 32.0F;
    const float BULLET_STARSHIP_HEIGHT = 28.0F;

    constexpr std::array<float, 3> BULLET_STARSHIP_FRAMES = {1.0F, 35.0F, 69.0F};

    class BulletStarshipAnimation : public AAnimation {
    public:
        BulletStarshipAnimation(float startX, float startY) : AAnimation(startX, startY, BULLET_STARSHIP_WIDTH, BULLET_STARSHIP_HEIGHT) {}

        RectFloat update() override {
            RectFloat frame = getCurrentFrame();

            if (_frameIndex == BULLET_STARSHIP_FRAMES.size() - 1)
                _frameIndex = 0;
            frame.left = BULLET_STARSHIP_FRAMES[_frameIndex];
            _frameIndex++;
            setCurrentFrame(frame);
            return getCurrentFrame();
        }

    private:
        int _frameIndex = 0;
    };
}
