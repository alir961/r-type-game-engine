/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <engine/modules/IModule.hpp>
#include <vector>
#include <SFML/Graphics.hpp>

namespace RType {

    struct Particle {
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Color color;
        float lifespan;
    };

    class ParticleModule : public IModule {
    public:
        void load() override;
        void unload() override;

        /**
         * @brief Adds a particle to the particle module.
         * @param particle The particle to add.
         */
        void addParticle(const Particle& particle);

        /**
         * @brief Updates all particles in the module.
         */
        void update();

    private:
        std::vector<Particle> _particles;
    };
}
