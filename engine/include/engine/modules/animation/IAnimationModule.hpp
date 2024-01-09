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

        virtual void addAnimation(const std::string &entityName) = 0;
        virtual sf::FloatRect update(const std::string &entityName, float deltaTime) = 0;
    };
}
