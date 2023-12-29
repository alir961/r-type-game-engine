/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

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

void RType::SoundModule::load() {
    std::cout << "Load Sound Module\n";
}

void RType::SoundModule::unload() {
    std::cout << "Unload Sound Module\n";
}

void RType::SoundModule::loadSound(int id, const std::string &soundPath, float volume) {
    if (soundBuffers_.find(id) != soundBuffers_.end())
        throw std::runtime_error("Sound already loaded");
    soundBuffers_[id].loadFromFile(soundPath);
    sounds_[id] = {id, soundPath, volume};
}

void RType::SoundModule::playSound(int id) {
    if (soundBuffers_.find(id) == soundBuffers_.end())
        throw std::runtime_error("Sound not loaded");
    sf::Sound sound;
    sound.setBuffer(soundBuffers_[id]);
    sound.setVolume(sounds_[id].volume);
    sound.play();
}

void RType::SoundModule::playAllSounds() {
    for (auto &sound : soundBuffers_) {
        sf::Sound sound_;
        sound_.setBuffer(sound.second);
        sound_.setVolume(sounds_[sound.first].volume);
        sound_.play();
    }
}

void RType::SoundModule::playLoopSound(int id) {
    if (soundBuffers_.find(id) == soundBuffers_.end())
        throw std::runtime_error("Sound not loaded");
    sf::Sound sound;
    sound.setBuffer(soundBuffers_[id]);
    sound.setVolume(sounds_[id].volume);
    sound.setLoop(true);
    sound.play();
}

void RType::SoundModule::stopSound(int id) {
    if (soundBuffers_.find(id) == soundBuffers_.end())
        throw std::runtime_error("Sound not loaded");
    sf::Sound sound;
    sound.setBuffer(soundBuffers_[id]);
    sound.setVolume(sounds_[id].volume);
    sound.stop();
}

std::vector<int> RType::SoundModule::stopAllSounds() {
    std::vector<int> failedStopIds;
    for (auto &sound : soundBuffers_) {
        sf::Sound sound_;
        sound_.setBuffer(sound.second);
        sound_.setVolume(sounds_[sound.first].volume);
        if (sound_.getStatus() == sf::SoundSource::Status::Playing) {
            sound_.stop();
            failedStopIds.push_back(sound.first);
        }
    }
    return failedStopIds;
}

void RType::SoundModule::mute() {
    isMuted_ = !isMuted_;
    for (auto &sound : soundBuffers_) {
        sf::Sound sound_;
        sound_.setBuffer(sound.second);
        sound_.setVolume(sounds_[sound.first].volume);
        if (isMuted_)
            sound_.setVolume(0);
        else
            sound_.setVolume(sounds_[sound.first].volume);
    }
}
