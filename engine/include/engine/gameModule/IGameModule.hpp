/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-timothe.medico
** File description:
** IGameModule
*/

#pragma once

class IGameModule {
public:
    virtual bool Initialize() = 0;
    virtual void Update() = 0;
    virtual void Shutdown() = 0;
    virtual ~IGameModule() = default;
};
