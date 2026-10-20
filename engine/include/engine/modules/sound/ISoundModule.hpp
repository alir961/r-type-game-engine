/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ISoundModule.hpp
*/

#pragma once

#include <string>
#include "engine/modules/IModule.hpp"

namespace RType {

    /**
     * @brief Sound effects and background music.
     */
    class ISoundModule : public IModule {
    public:
        void load() override = 0;
        void unload() override = 0;

        /**
         * @brief Play a short sound; several can overlap.
         * @param path Sound file, loaded the first time it is played
         * @param volume 0 to 100, scaled by the master volume
         */
        virtual void playSound(const std::string &path, float volume = 100.0F) = 0;

        /**
         * @brief Loop a music file. Playing the music already running does nothing.
         */
        virtual void playMusic(const std::string &path, float volume = 100.0F) = 0;

        virtual void stopMusic() = 0;

        /**
         * @param volume Master volume, 0 to 100
         */
        virtual void setVolume(float volume) = 0;

        [[nodiscard]] virtual float getVolume() const = 0;
    };

}
