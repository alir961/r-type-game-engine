/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

namespace RType {

    class IModule {
    public:
        virtual ~IModule() = default;

        virtual void load() = 0;
        virtual void unload() = 0;
    };

}
