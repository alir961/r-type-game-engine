/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** IAnimationModule.hpp
*/

#pragma once

#include "engine/modules/IModule.hpp"
#include "engine/ecs/Entity.hpp"
#include "IAnimation.hpp"
#include <memory>

namespace RType {

    class IAnimationModule : public IModule {
    public:
        void load() override = 0;
        void unload() override = 0;

        /**
         * @brief Create a new animation for an entity type.
         *
         * Every graphic entity owns its own animation, so entities of the same
         * type don't advance each other's frames.
         *
         * @param entityName Entity type (first word of the entity name, e.g. "monster")
         * @return A fresh animation positioned on its first frame
         */
        virtual AnimationPtr createAnimation(const std::string &entityName) = 0;
    };
}
