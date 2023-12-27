/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ResourceManager.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>

namespace RType {

    class ResourceManager {
    public:
        ResourceManager() = default;

        void loadTexture(const std::string& name, const std::string& filename);
        void loadSound(const std::string& name, const std::string& filename);

        sf::Texture& getTexture(const std::string& name);
        sf::SoundBuffer& getSound(const std::string& name);

    private:
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::SoundBuffer> sounds;
    };

} // namespace RType
