/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <engine/modules/IModule.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>


namespace RType {

    class SoundModule : public IModule {
    public:
        void load() override;
        void unload() override;

        struct SoundInfo {
            int id;
            std::string path;
            float volume;
        }; using SoundMap = std::map<int, SoundInfo>;

        void loadSound(int id, const std::string& soundPath, float volume);
        void playSound(int id);
        void playAllSounds();
        void playLoopSound(int id);
        void stopSound(int id);
        std::vector<int> stopAllSounds();
        void mute();

        private:
            bool isMuted_;
            SoundMap sounds_;
            std::map<int, sf::SoundBuffer> soundBuffers_;
            std::vector<int> failedStopIds_;
    };

}
