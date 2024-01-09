/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#pragma once

#include "PlayerAnimation.hpp"
#include <iostream>
#include <memory>

namespace RType {
    class IAnimationFactory {
    public:
        static std::shared_ptr<IAnimation> createAnimation(const std::string &entityName) {
            if (entityName == "turquoisePlayer")
                return std::make_shared<PlayerAnimation>(0, 0);
            if (entityName == "purplePlayer")
                return std::make_shared<PlayerAnimation>(0, 19);
            if (entityName == "greenPlayer")
                return std::make_shared<PlayerAnimation>(0, 36);
            if (entityName == "redPlayer")
                return std::make_shared<PlayerAnimation>(0, 53);
            if (entityName == "bluePlayer")
                return std::make_shared<PlayerAnimation>(0, 70);
            if (entityName == "bulletPlayer")
                return std::make_shared<PlayerAnimation>(101, 118);
            return std::make_shared<PlayerAnimation>(0, 19);
        }
    };
}
