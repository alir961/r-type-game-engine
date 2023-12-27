/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ResourceManager.cpp
*/

#include "ResourceManager.hpp"

using namespace RType;

void ResourceManager::loadTexture(const std::string& name, const std::string& filename) {
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        textures[name] = texture;
    }
}

void ResourceManager::loadSound(const std::string& name, const std::string& filename) {
    sf::SoundBuffer sound;
    if (sound.loadFromFile(filename)) {
        sounds[name] = sound;
    }
}

sf::Texture& ResourceManager::getTexture(const std::string& name) {
    return textures.at(name);
}

sf::SoundBuffer& ResourceManager::getSound(const std::string& name) {
    return sounds.at(name);
}
