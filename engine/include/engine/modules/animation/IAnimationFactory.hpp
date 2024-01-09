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
                return std::make_shared<PlayerAnimation>(0, PLAYER_HEIGHT * 1);
            if (entityName == "greenPlayer")
                return std::make_shared<PlayerAnimation>(0, PLAYER_HEIGHT * 2);
            if (entityName == "redPlayer")
                return std::make_shared<PlayerAnimation>(0, PLAYER_HEIGHT * 3);
            if (entityName == "bluePlayer")
                return std::make_shared<PlayerAnimation>(0, PLAYER_HEIGHT * 4);
            return std::make_shared<PlayerAnimation>(0, 0);
        }
    };
}
