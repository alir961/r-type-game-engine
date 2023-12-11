/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** ConsoleModule
*/

#pragma once
#include "IGameModule.hpp"
#include <string>

/**
 * @brief ConsoleModule abstarct class to implement Console
 */
class AConsoleModule : public IGameModule {
public:
    /**
     * @brief PrintConsole print message in console for debug
     * @param message to print
     */
    virtual void PrintConsole(const std::string& message) = 0;
};