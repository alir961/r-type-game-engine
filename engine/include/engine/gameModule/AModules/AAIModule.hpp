/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** AIModule
*/

#pragma once
#include "IGameModule.hpp"

/**
 * @brief AIModule abstarct class to implement AI
 */
class AAIModule : public IGameModule {
public:
    /**
     * @brief AssignAI load AI for entity
     */
    virtual void AssignAI() = 0;
};
