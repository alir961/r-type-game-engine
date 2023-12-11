/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** AudioModule
*/

#pragma once
#include "IGameModule.hpp"
#include <string>

/**
 * @brief AudioModule abstarct class to implement Audio
 */
class AAudioModule : public IGameModule {
public:
    /**
     * @brief PlayAudio play audio
     * @param name of audio
     */
    virtual void PlayAudio(const std::string& name) = 0;

    /**
     * @brief StopAudio stop audio
     */
    virtual void StopAudio() = 0;

    /**
     * @brief StopAllAudio stop list of audio
     */
    virtual void StopAllAudio() = 0;
};

