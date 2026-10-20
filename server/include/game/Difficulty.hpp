/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Difficulty.hpp
*/

#pragma once

#include <optional>
#include <string>

namespace RType {

    enum class Difficulty {
        EASY,
        NORMAL,
        HARD,
    };

    /**
     * @brief What a difficulty level changes: how often enemies come, how tough and how fast they are.
     */
    struct DifficultySettings {
        float monsterEverySeconds;      /**< Delay between two bio-drones. */
        float starshipEverySeconds;     /**< Delay between two raiders. */
        float starshipFireEverySeconds; /**< Delay between two volleys of the raiders. */
        int monsterHealth;
        int monsterSpeed;
        int starshipHealth;
        int starshipSpeed;
        int enemyShotDamage;            /**< Damage of a raider fireball. */
    };

    inline const DifficultySettings &getDifficultySettings(Difficulty difficulty) {
        static const DifficultySettings easy = {4.5f, 7.0f, 3.0f, 300, 2, 1800, 4, 150};
        static const DifficultySettings normal = {3.0f, 4.0f, 2.0f, 500, 2, 3000, 5, 300};
        static const DifficultySettings hard = {1.5f, 2.5f, 1.2f, 650, 3, 4000, 6, 450};

        switch (difficulty) {
            case Difficulty::EASY:
                return easy;
            case Difficulty::HARD:
                return hard;
            default:
                return normal;
        }
    }

    inline std::string difficultyToString(Difficulty difficulty) {
        switch (difficulty) {
            case Difficulty::EASY:
                return "easy";
            case Difficulty::HARD:
                return "hard";
            default:
                return "normal";
        }
    }

    inline std::optional<Difficulty> parseDifficulty(const std::string &name) {
        if (name == "easy")
            return Difficulty::EASY;
        if (name == "normal")
            return Difficulty::NORMAL;
        if (name == "hard")
            return Difficulty::HARD;
        return std::nullopt;
    }

}
