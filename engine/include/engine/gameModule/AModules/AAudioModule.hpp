/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** AudioModule
*/

#pragma once
#include "../IGameModule.hpp"
#include <string>

/**
 * @class AAudioModule
 * @brief Abstract class representing an audio module for the game.
 */
class AAudioModule : public IGameModule {
public:

   /**
     * @brief Pure virtual function to play audio with a given name.
     * @param name The name of the audio file to play.
    */
    virtual void PlayAudio(const std::string& name) = 0;

   /**
     * @brief Pure virtual function to stop the currently playing audio.
    */
    virtual void StopAudio() = 0;

    /**
     * @brief Pure virtual function to stop all audio playback.
    */
    virtual void StopAllAudio() = 0;
};

