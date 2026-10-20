/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Effects.hpp
*/

#pragma once

#include <numbers>
#include <string>
#include "engine/modules/ModuleProvider.hpp"
#include "engine/modules/graphical/IGraphicalModule.hpp"
#include "engine/modules/particle/IParticleModule.hpp"
#include "engine/modules/sound/ISoundModule.hpp"

namespace RType {

    /**
     * @brief Sound effects and music, when the sound module is loaded (it can be switched off in the options).
     */
    namespace Audio {
        constexpr const char *SOUNDS_PATH = "client/assets/sounds/";

        inline ISoundModule *getModule() {
            return ModuleProvider::getInstance()->get<ISoundModule>(ModuleType::SOUND);
        }

        /**
         * @param name File name in client/assets/sounds, without ".wav"
         * @param volume 0 to 100
         */
        inline void play(const std::string &name, float volume = 100.0F) {
            if (ISoundModule *sound = getModule())
                sound->playSound(SOUNDS_PATH + name + ".wav", volume);
        }

        inline void playMusic(const std::string &name, float volume = 45.0F) {
            if (ISoundModule *sound = getModule())
                sound->playMusic(SOUNDS_PATH + name + ".wav", volume);
        }

        inline void stopMusic() {
            if (ISoundModule *sound = getModule())
                sound->stopMusic();
        }
    }

    /**
     * @brief Particle effects, when the particle module is loaded.
     */
    namespace Particles {
        constexpr float PI = std::numbers::pi_v<float>;

        inline IParticleModule *getModule() {
            return ModuleProvider::getInstance()->get<IParticleModule>(ModuleType::PARTICLE);
        }

        /**
         * @brief Draw every live particle in one call.
         */
        inline void draw() {
            IParticleModule *particles = getModule();
            IGraphicalModule *graphical = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);

            if (particles != nullptr && graphical != nullptr && particles->getCount() > 0)
                graphical->drawSquares(particles->getSquares());
        }

        inline void emit(const ParticleBurst &burst) {
            if (IParticleModule *particles = getModule())
                particles->emit(burst);
        }

        /**
         * @brief Fire, smoke and debris thrown all around.
         * @param scale 1 for a small enemy, bigger for bigger ships
         */
        inline void explosion(const Vector2f &center, float scale) {
            emit({.position = center, .count = static_cast<int>(40 * scale), .color = {255, 150, 50, 255},
                  .speed = 260.0F * scale, .lifetime = 0.7F, .size = 7.0F * scale});
            emit({.position = center, .count = static_cast<int>(20 * scale), .color = {255, 240, 180, 255},
                  .speed = 420.0F * scale, .lifetime = 0.35F, .size = 4.0F});
            emit({.position = center, .count = static_cast<int>(14 * scale), .color = {110, 110, 140, 140},
                  .speed = 90.0F * scale, .lifetime = 1.1F, .size = 12.0F * scale});
        }

        /**
         * @brief A few sparks where something got hit.
         */
        inline void sparks(const Vector2f &position, const Color::RGB &color, int count = 10) {
            emit({.position = position, .count = count, .color = color, .speed = 360.0F, .lifetime = 0.35F, .size = 7.0F});
        }

        /**
         * @brief Exhaust puff behind a ship.
         * @param direction Where the exhaust goes (PI = to the left)
         */
        inline void trail(const Vector2f &position, const Color::RGB &color, float direction) {
            emit({.position = position, .count = 2, .color = color, .speed = 240.0F, .lifetime = 0.35F,
                  .size = 11.0F, .direction = direction, .spread = 0.45F});
        }
    }

}
