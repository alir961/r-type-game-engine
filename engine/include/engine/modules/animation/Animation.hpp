/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#pragma once

#include "IAnimation.hpp"

namespace RType {

    const float BASE_SPEED = 0.1F;

    class Animation : public IAnimation {
    public:

        Animation(float startX, float startY, float width, float height) {
            _currentFrame = sf::FloatRect (startX, startY, width, height);
        }

        void setAnimationSpeed(float animationSpeed) {_animationSpeed = animationSpeed;};
        void setAnimationTime(float animationTime) {_animationTime = animationTime;};
        void setCurrentFrame(sf::FloatRect frame) {_currentFrame = frame;};

        [[nodiscard]] float getAnimationSpeed() const {return _animationSpeed;};
        [[nodiscard]] float getAnimationTime() const {return _animationTime;};
        [[nodiscard]] sf::FloatRect getCurrentFrame() const {return _currentFrame;};

    private:
        sf::FloatRect _currentFrame;
        float _animationTime = 0.0F;
        float _animationSpeed = BASE_SPEED;
    };
}
