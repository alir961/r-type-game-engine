/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** AIModule
*/

#pragma once
#include "engine/ecs/gameModule/IGameModule.hpp"

/**
 * @class AAIModule
 * @brief Abstract class representing an AI module for the game.
 */
class AAIModule : public IGameModule {
public:

    /**
     * @brief Pure virtual function to assign AI behavior to the module.
     */
    virtual void AssignAI() = 0;
};
