/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** CinematicModule
*/

#pragma once
#include "IGameModule.hpp"
#include <string>

class ACinematicModule : public IGameModule {
public:
    virtual void PlayCinematic(const std::string& name) = 0;
};
