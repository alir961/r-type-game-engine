/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include <iostream>
#include "SoundModule.hpp"

extern "C" {
RType::IModule *initializeSoundModule() {
    return new RType::SoundModule();
}

void destroy(RType::SoundModule *library) {
    delete library;
}
}

void RType::SoundModule::load() {
    std::cout << "Load Sound Module\n";
}

void RType::SoundModule::unload() {
    std::cout << "Unload Sound Module\n";
}
