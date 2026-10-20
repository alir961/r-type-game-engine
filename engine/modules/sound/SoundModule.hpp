/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SoundModule.hpp
*/

#pragma once

#include <array>
#include <map>
#include <memory>
#include <string>
#include <SFML/Audio.hpp>
#include "engine/modules/sound/ISoundModule.hpp"

namespace RType {

    /**
     * @brief Sound module backed by SFML audio.
     *
     * Short sounds play on a fixed pool of voices so they can overlap; the music streams from disk.
     */
    class SoundModule : public ISoundModule {
    public:
        static constexpr std::size_t VOICES = 32;

        void load() override;
        void unload() override;

        void playSound(const std::string &path, float volume) override;
        void playMusic(const std::string &path, float volume) override;
        void stopMusic() override;
        void setVolume(float volume) override;
        [[nodiscard]] float getVolume() const override;

    private:
        std::map<std::string, sf::SoundBuffer> _buffers;
        std::array<sf::Sound, VOICES> _voices;
        sf::Music _music;
        std::string _musicPath;
        float _musicVolume = 100.0F;
        float _volume = 70.0F;

        const sf::SoundBuffer *getBuffer(const std::string &path);
    };

}
