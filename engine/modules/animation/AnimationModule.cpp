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
    addAnimation("turquoisePlayer");
    addAnimation("playerStarship");
    addAnimation("purplePlayer");
    addAnimation("greenPlayer");
    addAnimation("redPlayer");
    addAnimation("bluePlayer");
}

void RType::AnimationModule::unload() {
    std::cout << "Unload AnimationModule...\n";
}

void RType::AnimationModule::addAnimation(const std::string &entityName) {
    std::shared_ptr<IAnimation> animation = IAnimationFactory::createAnimation(entityName);

    _animations.try_emplace(entityName, animation);
}

sf::FloatRect RType::AnimationModule::update(const std::string &entityName) {
    auto animIter = _animations.find(entityName);
    if (animIter != _animations.end())
        return animIter->second->update();
    return {};
}

