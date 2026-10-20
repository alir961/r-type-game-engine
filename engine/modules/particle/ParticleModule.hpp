/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ParticleModule.hpp
*/

#pragma once

#include <random>
#include <vector>
#include "engine/modules/particle/IParticleModule.hpp"

namespace RType {

    struct Particle {
        Vector2f position;
        Vector2f velocity;
        Color::RGB color;
        float size;
        float lifetime;  /**< Remaining time, in seconds. */
        float duration;  /**< Total lifetime, to fade out and shrink. */
    };

    /**
     * @brief Simple particle system: particles fly, slow down, shrink and fade.
     */
    class ParticleModule : public IParticleModule {
    public:
        static constexpr std::size_t MAX_PARTICLES = 4000;

        void load() override;
        void unload() override;

        void emit(const ParticleBurst &burst) override;
        void update(float deltaTime) override;
        [[nodiscard]] const std::vector<ColoredSquare> &getSquares() override;
        void clear() override;
        [[nodiscard]] std::size_t getCount() const override;

    private:
        std::vector<Particle> _particles;
        std::vector<ColoredSquare> _squares; /**< Reused every frame, drawn in one call. */
        std::mt19937 _random{std::random_device{}()};
    };
}
