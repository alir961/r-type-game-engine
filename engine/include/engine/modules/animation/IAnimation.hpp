/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#pragma once

namespace RType {
    class IAnimation {
    public:
        virtual ~IAnimation() = default;

        virtual sf::FloatRect update(float deltaTime) = 0;
    };;
}