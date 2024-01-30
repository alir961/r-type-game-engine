/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** StarshipAnimation.hpp
*/

#pragma once

#include <array>
#include "../AAnimation.hpp"

namespace RType {

    const float STARSHIP_WIDTH = 32.0F;
    const float STARSHIP_HEIGHT = 22.0F;

    constexpr std::array<float, 8> STARSHIP_FRAMES = {1.0F, 34.0F, 67.0F, 100.0F, 133.0F, 166.0F, 199.0F, 232.0F};

    class StarshipAnimation : public AAnimation {
    public:
        StarshipAnimation(float startX, float startY) : AAnimation(startX, startY, STARSHIP_WIDTH, STARSHIP_HEIGHT) {}

        RectFloat update() override {
            RectFloat frame = getCurrentFrame();

            if (_frameIndex == STARSHIP_FRAMES.size() - 1)
                _frameIndex = 0;
            frame.left = STARSHIP_FRAMES[_frameIndex];
            _frameIndex++;
            setCurrentFrame(frame);
            return getCurrentFrame();
        }

    private:
        int _frameIndex = 0;
    };
}
