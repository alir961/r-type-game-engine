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

    struct SoundDetails {
        std::string path;
        float volume;
    };

    using SoundMap = std::map<int, SoundDetails>;

    class SoundModule : public IModule {
    public:
        void load() override;
        void unload() override;

        /**
         * @brief Loads a sound with the specified ID, file path, and volume.
         * @param soundId The ID of the sound.
         * @param soundPath The file path to the sound.
         * @param volume The volume of the sound.
         */
        void loadSound(int soundId, const std::string &soundPath, float volume);

        /**
         * @brief Plays the sound with the specified ID.
         * @param soundId The ID of the sound to play.
         */
        void playSound(int soundId);

        /**
         * @brief Plays all loaded sounds.
         */
        void playAllSounds();

        /**
         * @brief Plays the sound with the specified ID in a loop.
         * @param soundId The ID of the sound to play in a loop.
         */
        void playLoopSound(int soundId);

        /**
         * @brief Stops the sound with the specified ID.
         * @param soundId The ID of the sound to stop.
         */
        void stopSound(int soundId);

        /**
         * @brief Stops all playing sounds and returns their IDs.
         * @return A vector containing the IDs of stopped sounds.
         */
        std::vector<int> stopAllSounds();

        /**
         * @brief Toggles the mute state of the sound module.
         */
        void toggleMute();

        private:
            bool _muted;
            SoundMap _sounds;
            std::map<int, sf::SoundBuffer> _soundBuffers;
            std::vector<int> _failedStopIds;
    };

}
