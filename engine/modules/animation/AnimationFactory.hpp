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
#include "entity/StaticAnimation.hpp"
#include "entity/BulletStarshipAnimation.hpp"
#include "entity/StarshipAnimation.hpp"
#include "entity/ExplosionAnimation.hpp"
#include <memory>
#include <string>

namespace RType {

    /**
     * Row of each player color in client/assets/sprites/player.png.
     */
    constexpr int TURQUOISE_ROW = 0;
    constexpr int PURPLE_ROW = 1;
    constexpr int GREEN_ROW = 2;
    constexpr int RED_ROW = 3;
    constexpr int BLUE_ROW = 4;

    class AnimationFactory {
    public:
        static AnimationPtr createAnimation(const std::string &entityName) {
            if (entityName == "turquoisePlayer")
                return createPlayer(TURQUOISE_ROW);
            if (entityName == "purplePlayer")
                return createPlayer(PURPLE_ROW);
            if (entityName == "greenPlayer")
                return createPlayer(GREEN_ROW);
            if (entityName == "redPlayer")
                return createPlayer(RED_ROW);
            if (entityName == "bluePlayer")
                return createPlayer(BLUE_ROW);
            if (entityName == "bulletPlayer")
                return std::make_shared<BulletAnimation>();
            if (entityName == "monster")
                return std::make_shared<MonsterAnimation>();
            if (entityName == "static")
                return std::make_shared<StaticAnimation>();
            if (entityName == "bulletStarship")
                return std::make_shared<BulletStarshipAnimation>();
            if (entityName == "starship")
                return std::make_shared<StarshipAnimation>();
            if (entityName == "explosion")
                return std::make_shared<ExplosionAnimation>();
            return createPlayer(TURQUOISE_ROW);
        }

    private:
        static AnimationPtr createPlayer(int row) {
            return std::make_shared<PlayerAnimation>(static_cast<float>(row));
        }
    };

}
