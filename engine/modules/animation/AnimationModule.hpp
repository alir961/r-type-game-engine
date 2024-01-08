/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AnimationModule.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "engine/modules/animation/IAnimationModule.hpp"
#include "engine/modules/animation/Animation.hpp"

namespace RType {
    class AnimationModule :  public IAnimationModule {
    public:
        void load() override;
        void unload() override;

        AnimationModule() = default;

        void addAnimation(const std::string &entityName, const std::shared_ptr<Animation> &animation) override;
    private:
        std::map<std::string, std::shared_ptr<Animation>> _animations;
    };

}
