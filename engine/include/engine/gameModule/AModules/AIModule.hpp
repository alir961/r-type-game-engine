/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** AIModule
*/

#pragma once
#include "IGameModule.hpp"

class AIModule : public IGameModule {
public:
    virtual void AssignAI() = 0;
};
