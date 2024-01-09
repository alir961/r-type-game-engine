/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerBulletAnimation.hpp
*/

#pragma once

#include "Animation.hpp"

namespace RType {
    const float PBULLET_WIDTH = 14.0F;
    const float PBULLET_HEIGHT = 14.0F;
    const enum class Coordinates {
        FRAME0 = 101,
        FRAME1 = 118,
        FRAME2 = 135,
        FRAME3 = 152
    };

    class PlayerBulletAnimation : public Animation {
    public:
        PlayerBulletAnimation(float startX, float startY) : Animation(startX, startY, PBULLET_WIDTH, PBULLET_HEIGHT) {}
        sf::FloatRect update() override {
            sf::FloatRect frame = getCurrentFrame();
            switch (_currentFrame) {
                case Coordinates::FRAME0:
                    _currentFrame = Coordinates::FRAME1;
                    frame.left = 118;
                    break;
                case Coordinates::FRAME1:
                    _currentFrame = Coordinates::FRAME2;
                    frame.left = 135;
                    break;
                case Coordinates::FRAME2:
                    _currentFrame = Coordinates::FRAME3;
                    frame.left = 152;
                    break;
                case Coordinates::FRAME3:
                    _currentFrame = Coordinates::FRAME0;
                    frame.left = 101;
                    break;
            }
            setCurrentFrame(frame);
            return getCurrentFrame();
        }
    private:
        Coordinates _currentFrame;
    };
}
