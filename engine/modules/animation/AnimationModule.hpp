/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AnimationModule.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

namespace Engine {

    struct AnimationFrame {
        sf::IntRect frameRect;
        float duration;
    };

    class AnimationModule {
    public:
        AnimationModule() = default;

        void addAnimation(const std::string& id, const std::vector<AnimationFrame>& frames);
        void updateAnimation(const std::string& id, float deltaTime);
        const sf::IntRect& getCurrentFrame(const std::string& id) const;

    private:
        struct Animation {
            std::vector<AnimationFrame> frames;
            float totalTime = 0.0f;
            size_t currentFrameIndex = 0;
        };

        std::unordered_map<std::string, Animation> animations;
    };

}
