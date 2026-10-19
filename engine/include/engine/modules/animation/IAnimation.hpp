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

        virtual RectFloat update() = 0;
    };

    using AnimationPtr = std::shared_ptr<IAnimation>;

}