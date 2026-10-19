/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** STATICAnimation.hpp
*/

#pragma once

#include <array>
#include "../AAnimation.hpp"

namespace RType {

    const float STATIC_WIDTH = 122.0F;
    const float STATIC_HEIGHT = 122.0F;

    constexpr std::array<float, 8> STATIC_FRAMES = {14.0F, 171.0F, 329.0F, 489.0F, 647.0F, 806.0F, 964.0F, 1122.0F};

    class StaticAnimation : public AAnimation {
    public:
        StaticAnimation(float startX, float startY) : AAnimation(startX, startY, STATIC_WIDTH, STATIC_HEIGHT) {}

        RectFloat update() override {
            RectFloat frame = getCurrentFrame();

            if (_frameIndex == STATIC_FRAMES.size() - 1)
                _frameIndex = 0;
            frame.left = STATIC_FRAMES[_frameIndex];
            _frameIndex++;
            setCurrentFrame(frame);
            return getCurrentFrame();
        }

    private:
        int _frameIndex = 0;
    };
}
