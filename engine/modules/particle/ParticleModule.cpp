/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ParticleModule.cpp
*/

#include <algorithm>
#include <cmath>
#include "ParticleModule.hpp"

extern "C" {
RType::IModule *initializeParticleModule() {
    return new RType::ParticleModule();
}

void destroy(RType::ParticleModule *library) {
    delete library;
}
}

void RType::ParticleModule::load() {
    _particles.reserve(MAX_PARTICLES);
}

void RType::ParticleModule::unload() {
    clear();
}

void RType::ParticleModule::emit(const RType::ParticleBurst &burst) {
    std::uniform_real_distribution<float> unit(0.0F, 1.0F);

    for (int i = 0; i < burst.count && _particles.size() < MAX_PARTICLES; i++) {
        const float angle = burst.direction + (unit(_random) - 0.5F) * burst.spread;
        const float speed = burst.speed * (0.3F + 0.7F * unit(_random));
        const float lifetime = burst.lifetime * (0.5F + 0.5F * unit(_random));

        _particles.push_back(Particle{
                .position = burst.position,
                .velocity = {std::cos(angle) * speed, std::sin(angle) * speed},
                .color = burst.color,
                .size = burst.size * (0.6F + 0.4F * unit(_random)),
                .lifetime = lifetime,
                .duration = lifetime,
        });
    }
}

void RType::ParticleModule::update(float deltaTime) {
    const float drag = std::pow(0.08F, deltaTime); // keeps ~8% of its speed after one second

    for (auto &particle: _particles) {
        particle.position.first += particle.velocity.first * deltaTime;
        particle.position.second += particle.velocity.second * deltaTime;
        particle.velocity.first *= drag;
        particle.velocity.second *= drag;
        particle.lifetime -= deltaTime;
    }
    std::erase_if(_particles, [](const Particle &particle) { return particle.lifetime <= 0.0F; });
}

const std::vector<RType::ColoredSquare> &RType::ParticleModule::getSquares() {
    _squares.clear();
    for (const auto &particle: _particles) {
        const float life = particle.lifetime / particle.duration;
        Color::RGB color = particle.color;

        color.a = static_cast<ColorComponent>(static_cast<float>(color.a) * life);
        _squares.push_back({particle.position, particle.size * (0.4F + 0.6F * life), color});
    }
    return _squares;
}

void RType::ParticleModule::clear() {
    _particles.clear();
}

std::size_t RType::ParticleModule::getCount() const {
    return _particles.size();
}
