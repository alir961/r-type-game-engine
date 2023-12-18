/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** ConsoleModule
*/

#pragma once
#include "engine/ecs/gameModule/IGameModule.hpp"
#include <string>

/**
 * @class AConsoleModule
 * @brief Abstract class representing a console module for the game.
 */
class AConsoleModule : public IGameModule {
public:

    /**
     * @brief Pure virtual function to print a message to the game console.
     * @param message The message to be printed.
     */
    virtual void PrintConsole(const std::string& message) = 0;
};