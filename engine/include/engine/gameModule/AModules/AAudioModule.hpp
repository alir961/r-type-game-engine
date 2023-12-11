/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** AudioModule
*/

#pragma once
#include "IGameModule.hpp"
#include <string>

class AAudioModule : public IGameModule {
public:
    virtual void PlayAudio(const std::string& name) = 0;
    virtual void StopAudio() = 0;
    virtual void StopAllAudio() = 0;
};

