/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** IGameModule
*/

#pragma once

/**
 * @brief Interface for all game modules
 * @class IGameModule
 */
class IGameModule {
public:
    /**
     * @brief Initialize the module, called at the start of the game
     * @return true if success, false otherwise
     */
    virtual bool Initialize() = 0;

    /**
     * @brief Update the module, called each frame
     */
    virtual void Update() = 0;

    /**
     * @brief Shutdown the module, called at the end of the game
     */
    virtual void Shutdown() = 0;

    /**
     * @brief Destroy the module
     */
    virtual ~IGameModule() = default;
};
