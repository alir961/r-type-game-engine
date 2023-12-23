/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "./IComponent.hpp"
#include <iostream>

/**
 * @brief Base abstract for component.
 */
class AComponent : public IComponent {
public:
    /**
    * @brief Base update function.
    */
    virtual void update() = 0;

    AComponent() = default;
    ~AComponent() = default;
};
