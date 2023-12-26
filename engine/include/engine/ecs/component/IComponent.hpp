/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

namespace RType {
    /**
    * @brief Base interface for component.
    */
    class IComponent {
    public:
        /**
        * @brief Base update function.
        */
        virtual void update() = 0;

        virtual ~IComponent() = default;
    };
}