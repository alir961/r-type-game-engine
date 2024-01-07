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
        Background(const sf::RenderWindow &window, const std::vector<std::string>& imagePaths, const std::vector<float>& speeds);

        void update(float deltaTime);
        void draw(sf::RenderWindow& window);

    private:
        std::vector<sf::Texture> _textures;
        std::vector<sf::Sprite> _sprites;
        std::vector<float> _speeds;
    };

};
