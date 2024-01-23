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
    addAnimation("turquoisePlayer");
    addAnimation("playerStarship");
    addAnimation("purplePlayer");
    addAnimation("greenPlayer");
    addAnimation("redPlayer");
    addAnimation("bluePlayer");
    addAnimation("bulletPlayer");
    addAnimation("monster");
    addAnimation("static");
}

void RType::AnimationModule::unload() {
}

void RType::AnimationModule::addAnimation(const std::string &entityName) {
    AnimationPtr animation = AnimationFactory::createAnimation(entityName);

    _animations.try_emplace(entityName, animation);
}

RType::RectFloat RType::AnimationModule::update(const std::string &entityName) {
    if (const auto &iterator = _animations.find(entityName); iterator != _animations.end())
        return iterator->second->update();
    _logger->warn("Unable to find animation for " + entityName);
    return {};
}

