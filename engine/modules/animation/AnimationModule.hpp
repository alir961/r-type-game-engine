/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AnimationModule.hpp
*/

#pragma once

#include "engine/modules/animation/IAnimationModule.hpp"
#include "engine/modules/animation/IAnimation.hpp"
#include "AnimationFactory.hpp"

namespace RType {

    class AnimationModule :  public IAnimationModule {
    public:
        void load() override;
        void unload() override;

        AnimationModule() = default;

        AnimationPtr createAnimation(const std::string &entityName) override;
    };

}
