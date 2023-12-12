/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** IGameModule
*/

#pragma once

/**
 * @class IGameModule
 * @brief Interface class for game modules.
 */
class IGameModule {
public:
    /**
     * @brief Pure virtual function to initialize the game module.
     * @return True if initialization is successful, false otherwise.
     */
    virtual bool Initialize() = 0;

    /**
     * @brief Pure virtual function to update the game module.
     */
    virtual void Update() = 0;

    /**
     * @brief Pure virtual function to shut down the game module.
     */
    virtual void Shutdown() = 0;

    /**
     * @brief Virtual destructor for the game module interface.
     */
    virtual ~IGameModule() = default;
};
