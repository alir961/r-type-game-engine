/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
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

void RType::ParticleModule::load() {}

void RType::ParticleModule::unload() {}

void RType::ParticleModule::addParticle(const RType::Particle &particle) {
    _particles.push_back(particle);
}

void RType::ParticleModule::update() {
    for (auto &particle: _particles) {
        particle.position += particle.velocity;
        particle.lifespan -= 1;
    }

    _particles.erase(std::remove_if(_particles.begin(), _particles.end(), [](const Particle &particle) {
        return particle.lifespan <= 0;
    }), _particles.end());
}
