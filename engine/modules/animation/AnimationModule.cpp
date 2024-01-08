/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AnimationModule.cpp
*/

#include "AnimationModule.hpp"
#include <stdexcept>

namespace Engine {

    void AnimationModule::addAnimation(const std::string& id, const std::vector<AnimationFrame>& frames) {
        animations[id] = {frames, 0.0f, 0};
    }

    void AnimationModule::updateAnimation(const std::string& id, float deltaTime) {
        auto& anim = animations.at(id);

        anim.totalTime += deltaTime;
        if (anim.totalTime >= anim.frames[anim.currentFrameIndex].duration) {
            anim.totalTime -= anim.frames[anim.currentFrameIndex].duration;
            anim.currentFrameIndex = (anim.currentFrameIndex + 1) % anim.frames.size();
        }
    }

    const sf::IntRect& AnimationModule::getCurrentFrame(const std::string& id) const {
        const auto& anim = animations.at(id);
        return anim.frames[anim.currentFrameIndex].frameRect;
    }

}
