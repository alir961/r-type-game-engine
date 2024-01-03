/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace RType {
    class Background {
    public:
        Background(sf::RenderWindow &window, const std::vector<std::string>& imagePaths, const std::vector<float>& speeds);
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);
    private:
        std::vector<sf::Texture> textures;
        std::vector<sf::Sprite> sprites;
        std::vector<float> speeds;
    };
};
