/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** CinematicModule
*/

#pragma once
#include "engine/ecs/gameModule/IGameModule.hpp"
#include <string>

/**
 * @class ACinematicModule
 * @brief Abstract class representing a cinematic module for the game.
 */
class ACinematicModule : public IGameModule {
public:

    /**
     * @brief Pure virtual function to play a cinematic with a given name.
     * @param name The name of the cinematic to play.
     */
    virtual void PlayCinematic(const std::string& name) = 0;
};
