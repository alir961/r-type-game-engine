/*
** EPITECH PROJECT, 2023
** NEWRTYPE
** File description:
** ConsoleModule
*/

#pragma once
#include <engine/modules/IModule.hpp>
#include <vector>
#include <SFML/Graphics.hpp>

namespace RType {

    class ParticleModule : public IModule {
    public:
        void load() override;
        void unload() override;

        struct Particle {
            sf::Vector2f position;
            sf::Vector2f velocity;
            sf::Color color;
            float lifespan;
        };

        void addParticle(const Particle& particle);
        void update();

    private:
        std::vector<Particle> particles;
    };
}
