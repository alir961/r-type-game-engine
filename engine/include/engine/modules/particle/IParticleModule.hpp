/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** IParticleModule.hpp
*/

#pragma once

#include <cstddef>
#include <numbers>
#include <vector>
#include "engine/modules/IModule.hpp"
#include "engine/modules/graphical/DataCommon.hpp"

namespace RType {

    /**
     * @brief How a burst of particles is thrown.
     */
    struct ParticleBurst {
        Vector2f position;                       /**< Where the particles appear. */
        int count = 10;
        Color::RGB color = Color::White;
        float speed = 200.0F;                    /**< Maximum speed, in pixels per second. */
        float lifetime = 0.5F;                   /**< Maximum lifetime, in seconds. */
        float size = 4.0F;                       /**< Starting size, shrinks to nothing. */
        float direction = 0.0F;                  /**< Angle of the cone, in radians (0 = right). */
        float spread = 2.0F * std::numbers::pi_v<float>; /**< Width of the cone (2π = all around). */
    };

    /**
     * @brief Short-lived glowing particles: sparks, explosions, engine trails.
     */
    class IParticleModule : public IModule {
    public:
        void load() override = 0;
        void unload() override = 0;

        virtual void emit(const ParticleBurst &burst) = 0;

        virtual void update(float deltaTime) = 0;

        /**
         * @brief Every live particle as a square to draw, faded and shrunk by age.
         *
         * The module stays independent from the renderer: the game draws these
         * with IGraphicalModule::drawSquares.
         */
        [[nodiscard]] virtual const std::vector<ColoredSquare> &getSquares() = 0;

        virtual void clear() = 0;

        [[nodiscard]] virtual std::size_t getCount() const = 0;
    };

}
