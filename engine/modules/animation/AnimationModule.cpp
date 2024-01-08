/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AnimationModule.cpp
*/

#include "AnimationModule.hpp"

extern "C" {
RType::IModule *initializeAnimationModule() {
    return new RType::AnimationModule();
}

void destroy(RType::AnimationModule *library) {
    delete library;
}
}

void RType::AnimationModule::load() {
    std::cout << "Load AnimationModule...\n";
}

void RType::AnimationModule::unload() {
    std::cout << "Unload AnimationModule...\n";
}

void RType::AnimationModule::addAnimation(const std::string &entityName, const std::shared_ptr<IAnimation> &animation) {
    _animations.try_emplace(entityName, animation);
}

