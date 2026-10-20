/*
** EPITECH PROJECT, 2023
** engine
** File description:
** AnimationModule.cpp
*/

#include "AnimationModule.hpp"
#include "AnimationFactory.hpp"

extern "C" {
RType::IModule *initializeAnimationModule() {
    return new RType::AnimationModule();
}

void destroy(RType::AnimationModule *library) {
    delete library;
}
}

void RType::AnimationModule::load() {
}

void RType::AnimationModule::unload() {
}

RType::AnimationPtr RType::AnimationModule::createAnimation(const std::string &entityName) {
    return AnimationFactory::createAnimation(entityName);
}
