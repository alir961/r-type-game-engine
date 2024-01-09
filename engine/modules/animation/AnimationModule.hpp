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
#include "engine/modules/animation/IAnimation.hpp"
#include "engine/modules/animation/IAnimationFactory.hpp"

namespace RType {
    class AnimationModule :  public IAnimationModule {
    public:
        void load() override;
        void unload() override;

        AnimationModule() = default;

        void addAnimation(const std::string &entityName) override;
        sf::FloatRect update(const std::string &entityName, float deltaTime) override;
    private:
        std::map<std::string, std::shared_ptr<IAnimation>> _animations;
    };

}
