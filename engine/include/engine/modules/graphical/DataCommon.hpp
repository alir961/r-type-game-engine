/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <cstdint>
#include <memory>

namespace RType {

    using Vector2f = std::pair<float, float>;

    using ColorComponent = uint8_t;

    struct RectFloat {
        float left;
        float top;
        float width;
        float height;

        bool contains(Vector2f point) {
            if (point.first < left || point.second < top)
                return false;
            if (point.first > left + width || point.second > top + height)
                return false;
            return true;
        }
    };

    namespace Color {

        struct RGB {
            ColorComponent r;
            ColorComponent g;
            ColorComponent b;
            ColorComponent a;
        };

        static const RGB Black{0, 0, 0, 255};   //!< Black predefined color
        static const RGB White{255, 255, 255, 255};        //!< White predefined color
        static const RGB Red{255, 0, 0, 255};         //!< Red predefined color
        static const RGB Green{0, 255, 0, 255};       //!< Green predefined color
        static const RGB Blue{0, 0, 255, 255};        //!< Blue predefined color
        static const RGB Yellow{255, 255, 0, 255};    //!< Yellow predefined color
        static const RGB Magenta{255, 0, 255, 255};   //!< Magenta predefined color
        static const RGB Cyan{0, 255, 255, 255};      //!< Cyan predefined color
        static const RGB Transparent{0, 0, 0, 0};

    }

}