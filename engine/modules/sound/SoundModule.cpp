/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SoundModule.cpp
*/

#include <algorithm>
#include <iostream>
#include "SoundModule.hpp"

extern "C" {
RType::IModule *initializeSoundModule() {
    return new RType::SoundModule();
}

void destroy(RType::SoundModule *library) {
    delete library;
}
}

void RType::SoundModule::load() {}

void RType::SoundModule::unload() {
    // Stop everything before the buffers go away with the module.
    for (auto &voice: _voices)
        voice.stop();
    _music.stop();
}

const sf::SoundBuffer *RType::SoundModule::getBuffer(const std::string &path) {
    auto iterator = _buffers.find(path);

    if (iterator == _buffers.end()) {
        sf::SoundBuffer buffer;

        if (!buffer.loadFromFile(path)) {
            std::cerr << "Unable to load sound '" << path << "'\n";
            return nullptr;
        }
        iterator = _buffers.emplace(path, std::move(buffer)).first;
    }
    return &iterator->second;
}

void RType::SoundModule::playSound(const std::string &path, float volume) {
    const sf::SoundBuffer *buffer = getBuffer(path);

    if (buffer == nullptr || _volume <= 0.0F)
        return;
    // A free voice, or else the one closest to the end of its sound.
    auto voice = std::find_if(_voices.begin(), _voices.end(), [](const sf::Sound &sound) {
        return sound.getStatus() != sf::Sound::Playing;
    });
    if (voice == _voices.end()) {
        voice = std::max_element(_voices.begin(), _voices.end(), [](const sf::Sound &a, const sf::Sound &b) {
            return a.getPlayingOffset() < b.getPlayingOffset();
        });
    }
    voice->setBuffer(*buffer);
    voice->setVolume(std::clamp(volume, 0.0F, 100.0F) * _volume / 100.0F);
    voice->play();
}

void RType::SoundModule::playMusic(const std::string &path, float volume) {
    _musicVolume = volume;
    _music.setVolume(_musicVolume * _volume / 100.0F);
    if (path == _musicPath && _music.getStatus() == sf::Music::Playing)
        return;
    if (!_music.openFromFile(path)) {
        std::cerr << "Unable to open music '" << path << "'\n";
        return;
    }
    _musicPath = path;
    _music.setLoop(true);
    _music.play();
}

void RType::SoundModule::stopMusic() {
    _music.stop();
    _musicPath.clear();
}

void RType::SoundModule::setVolume(float volume) {
    _volume = std::clamp(volume, 0.0F, 100.0F);
    _music.setVolume(_musicVolume * _volume / 100.0F);
}

float RType::SoundModule::getVolume() const {
    return _volume;
}
