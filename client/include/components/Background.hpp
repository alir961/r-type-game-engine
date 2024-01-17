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
#include "engine/modules/graphical/ASprite.hpp"
#include "engine/modules/graphical/IGraphicalModule.hpp"
#include "engine/modules/ModuleProvider.hpp"

namespace RType {

    class Background {
    public:
        Background(const std::vector<std::string>& imagePaths, const std::vector<float>& speeds);

        void update(float deltaTime);
        void draw();

    private:
        IGraphicalModule *_module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        std::vector<SpriteComponent> _sprites;
        std::vector<float> _speeds;
    };

};
