/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** CinematicModule
*/

#pragma once
#include "IGameModule.hpp"
#include <string>

/**
 * @brief CinematicModule abstarct class to implement Cinematic
 */
class ACinematicModule : public IGameModule {
public:
    /**
     * @brief PlayCinematic play video cinematic
     * @param name of cinematic
     */
    virtual void PlayCinematic(const std::string& name) = 0;
};
