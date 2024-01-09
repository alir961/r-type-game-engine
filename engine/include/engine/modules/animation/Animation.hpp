/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#pragma once

#include "IAnimation.hpp"

namespace RType {

    class Animation : public IAnimation {
    public:

        Animation(float startX, float startY, float width, float height) {
            _currentFrame = sf::FloatRect (startX, startY, width, height);
        }

        void setCurrentFrame(sf::FloatRect frame) {_currentFrame = frame;};


        [[nodiscard]] sf::FloatRect getCurrentFrame() const {return _currentFrame;};

    private:
        sf::FloatRect _currentFrame;

    };
}
