/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#pragma once

#include <array>
#include "engine/modules/animation/IAnimation.hpp"

namespace RType {

    class AAnimation : public IAnimation {
    public:
        AAnimation(float startX, float startY, float width, float height) : _currentFrame{startX, startY, width, height} {}

        void setCurrentFrame(RectFloat frame) { _currentFrame = frame; };

        [[nodiscard]] RectFloat getCurrentFrame() const { return _currentFrame; };

    private:
        RectFloat _currentFrame;
    };
}
