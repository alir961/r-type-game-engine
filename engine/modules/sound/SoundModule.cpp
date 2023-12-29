/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include <iostream>
#include "SoundModule.hpp"
#include "engine/exception/ModuleException.hpp"

extern "C" {
RType::IModule *initializeSoundModule() {
    return new RType::SoundModule();
}

void destroy(RType::SoundModule *library) {
    delete library;
}
}

void RType::SoundModule::load() {
    std::cout << "Load Sound Module\n";
}

void RType::SoundModule::unload() {
    std::cout << "Unload Sound Module\n";
}

void RType::SoundModule::loadSound(int soundId, const std::string &soundPath, float volume) {
    if (!_soundBuffers.contains(soundId))
        throw ModuleException("Sound already loaded");
    _soundBuffers[soundId].loadFromFile(soundPath);
    _sounds[soundId] = {soundPath, volume};
}

void RType::SoundModule::playSound(int soundId) {
    sf::Sound sound;

    if (!_soundBuffers.contains(soundId))
        throw ModuleException("Sound not loaded");
    sound.setBuffer(_soundBuffers[soundId]);
    sound.setVolume(_sounds[soundId].volume);
    sound.play();
}

void RType::SoundModule::playAllSounds() {
    for (const auto &[id, sound] : _soundBuffers) {
        sf::Sound soundToPlay;

        soundToPlay.setBuffer(sound);
        soundToPlay.setVolume(_sounds[id].volume);
        soundToPlay.play();
    }
}

void RType::SoundModule::playLoopSound(int soundId) {
    sf::Sound sound;

    if (!_soundBuffers.contains(soundId))
        throw ModuleException("Sound not loaded");
    sound.setBuffer(_soundBuffers[soundId]);
    sound.setVolume(_sounds[soundId].volume);
    sound.setLoop(true);
    sound.play();
}

void RType::SoundModule::stopSound(int soundId) {
    sf::Sound sound;

    if (!_soundBuffers.contains(soundId))
        throw ModuleException("Sound not loaded");
    sound.setBuffer(_soundBuffers[soundId]);
    sound.setVolume(_sounds[soundId].volume);
    sound.stop();
}

std::vector<int> RType::SoundModule::stopAllSounds() {
    std::vector<int> failedStopIds;

    for (const auto &[id, sound] : _soundBuffers) {
        sf::Sound soundToStop;

        soundToStop.setBuffer(sound);
        soundToStop.setVolume(_sounds[id].volume);
        if (soundToStop.getStatus() == sf::SoundSource::Status::Playing) {
            failedStopIds.push_back(id);
            soundToStop.stop();
        }
    }
    return failedStopIds;
}

void RType::SoundModule::toggleMute() {
    _muted = !_muted;

    for (const auto &[id, sound] : _soundBuffers) {
        sf::Sound soundToMute;

        soundToMute.setBuffer(sound);
        if (_muted)
            soundToMute.setVolume(0);
        else
            soundToMute.setVolume(_sounds[id].volume);
    }
}
