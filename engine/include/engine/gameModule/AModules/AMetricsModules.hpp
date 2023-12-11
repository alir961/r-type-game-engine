/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** MetricsModules
*/

#pragma once
#include "IGameModule.hpp"
#include <string>

/**
 * @brief MetricsModule abstarct class to implement Metrics
 */
class AMetricsModule : public IGameModule {
public:
    /**
     * @brief GetFPS get FPS of game
     * @return FPS
     */
    virtual int GetFPS() const = 0;
};