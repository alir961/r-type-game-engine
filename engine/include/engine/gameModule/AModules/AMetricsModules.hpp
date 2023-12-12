/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** MetricsModules
*/

#pragma once
#include "../IGameModule.hpp"
#include <string>

/**
 * @class AMetricsModule
 * @brief Abstract class representing a metrics module for the game.
 */
class AMetricsModule : public IGameModule {
public:

    /**
     * @brief Pure virtual function to get the frames per second (FPS) of the game.
     * @return The current FPS of the game.
     */
    virtual int GetFPS() const = 0;
};