/*
** EPITECH PROJECT, 2023
** NEWRTYPE
** File description:
** ParticuleModule
*/

#include "ParticleModule.hpp"
#include <iostream>

extern "C" {
RType::IModule *initializeParticleModule() {
    return new RType::ParticleModule();
}

void destroy(RType::ParticleModule *library) {
    delete library;
}
}

void RType::ParticleModule::load() {
    std::cout << "Load Particle Module\n";
}

void RType::ParticleModule::unload() {
    std::cout << "Unload Particle Module\n";
}

void RType::ParticleModule::addParticle(const ParticleModule::Particle& particle) {
    particles.push_back(particle);
}


void RType::ParticleModule::update() {
    for (auto& particle : particles) {
        particle.position += particle.velocity;
        particle.lifespan -= 1;
    }
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](const Particle& particle) {
        return particle.lifespan <= 0;
    }), particles.end());
}
