/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** ConsoleModule
*/

#pragma once
#include "IGameModule.hpp"
#include <string>

class AConsoleModule : public IGameModule {
public:
    virtual void PrintConsole(const std::string& message) = 0;
};