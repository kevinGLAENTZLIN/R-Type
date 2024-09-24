/*
** EPITECH PROJECT, 2024
** R-Type - Components : Volume
** File description:
** Volume Component
*/

#include "Volume.hh"

Components::Volume::Volume(float masterVolume, float musicVolume, float sfxVolume):
    _masterVolume(masterVolume), _musicVolume(musicVolume), _sfxVolume(sfxVolume)
{}

float Components::Volume::getMasterVolume() const {
    return _masterVolume;
}

void Components::Volume::setMasterVolume(float volume) {
    _masterVolume = volume;
}

float Components::Volume::getMusicVolume() const {
    return _musicVolume;
}

void Components::Volume::setMusicVolume(float volume) {
    _musicVolume = volume;
}

float Components::Volume::getSfxVolume() const {
    return _sfxVolume;
}

void Components::Volume::setSfxVolume(float volume) {
    _sfxVolume = volume;
}
