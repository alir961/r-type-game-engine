/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AnimationModule.hpp
*/

#pragma once

#include <map>
#include <vector>
#include "engine/modules/animation/IAnimationModule.hpp"
#include "engine/modules/animation/IAnimation.hpp"
#include "AnimationFactory.hpp"
#include "engine/modules/logger/ILoggerModule.hpp"
#include "engine/modules/ModuleProvider.hpp"

namespace RType {

    class AnimationModule :  public IAnimationModule {
    public:
        void load() override;
        void unload() override;

        AnimationModule() = default;

        void addAnimation(const std::string &entityName) override;
        RectFloat update(const std::string &entityName) override;

    private:
        std::map<std::string, AnimationPtr> _animations;
        ILoggerModule *_logger = ModuleProvider::getInstance()->get<ILoggerModule>(ModuleType::LOGGER);
    };

}
