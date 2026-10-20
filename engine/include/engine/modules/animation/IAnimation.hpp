/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#pragma once

#include <memory>
#include "engine/modules/graphical/DataCommon.hpp"

namespace RType {

    class IAnimation {
    public:
        virtual ~IAnimation() = default;

        /**
         * @brief Advance to the next frame.
         * @return The texture rectangle of the new frame
         */
        virtual RectFloat update() = 0;

        /**
         * @return The texture rectangle of the current frame
         */
        [[nodiscard]] virtual RectFloat getCurrentFrame() const = 0;

        /**
         * @return Seconds each frame stays on screen
         */
        [[nodiscard]] virtual float getFrameDuration() const = 0;
    };

    using AnimationPtr = std::shared_ptr<IAnimation>;

}