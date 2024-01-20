/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#pragma once

#include "entity/PlayerAnimation.hpp"
#include "entity/BulletAnimation.hpp"
#include "entity/MonsterAnimation.hpp"
#include <iostream>
#include <memory>

namespace RType {

    constexpr int TURQUOISE_Y = 0;
    constexpr int PURPLE_Y = 19;
    constexpr int GREEN_Y = 36;
    constexpr int RED_Y = 53;
    constexpr int BLUE_Y = 70;
    constexpr int BULLET_X = 101;
    constexpr int BULLET_Y = 118;
    constexpr int MONSTER_Y = 67;

    class AnimationFactory {
    public:
        static AnimationPtr createAnimation(const std::string &entityName) {
            if (entityName == "turquoisePlayer")
                return createPlayer(TURQUOISE_Y);
            if (entityName == "purplePlayer")
                return createPlayer(PURPLE_Y);
            if (entityName == "greenPlayer")
                return createPlayer(GREEN_Y);
            if (entityName == "redPlayer")
                return createPlayer(RED_Y);
            if (entityName == "bluePlayer")
                return createPlayer(BLUE_Y);
            if (entityName == "bulletPlayer")
                return createBullet();
            if (entityName == "monster")
                return createMonster();
            return createPlayer(TURQUOISE_Y);
        }

    private:
        static AnimationPtr createPlayer(int color) {
            return std::make_shared<PlayerAnimation>(0, color);
        }

        static AnimationPtr createBullet() {
            return std::make_shared<BulletAnimation>(BULLET_X, BULLET_Y);
        }
        static AnimationPtr createMonster() {
            return std::make_shared<MonsterAnimation>(0, MONSTER_Y);
        }
    };

}
