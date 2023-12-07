/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** MetricsModules
*/

#pragma once
#include "IGameModule.hpp"
#include <string>

class MetricsModule : public IGameModule {
public:
    virtual int GetFPS() const = 0;
};