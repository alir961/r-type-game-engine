/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** IAnimationModule.hpp
*/

#pragma once

#include "engine/modules/IModule.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include "engine/ecs/Entity.hpp"
#include "IAnimation.hpp"

namespace RType {

    class IAnimationModule : public IModule {
    public:
        void load() override = 0;
        void unload() override = 0;

        virtual void addAnimation(const std::string &entityName, const std::shared_ptr<IAnimation> &animation) = 0;
    };
}
