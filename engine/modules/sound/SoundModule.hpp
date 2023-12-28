/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <engine/modules/IModule.hpp>

namespace RType {

    class SoundModule : public IModule {
    public:
        void load() override;
        void unload() override;
    };

}
