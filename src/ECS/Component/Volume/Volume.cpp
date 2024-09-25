/*
** EPITECH PROJECT, 2024
** R-Type - Components : Volume
** File description:
** Volume Component
*/

#include "Volume.hh"

ECS::Components::Volume::Volume(float masterVolume, float musicVolume, float sfxVolume):
    _masterVolume(masterVolume), _musicVolume(musicVolume), _sfxVolume(sfxVolume)
{}

float ECS::Components::Volume::getMasterVolume() const {
    return _masterVolume;
}

void ECS::Components::Volume::setMasterVolume(float volume) {
    _masterVolume = volume;
}

float ECS::Components::Volume::getMusicVolume() const {
    return _musicVolume;
}

void ECS::Components::Volume::setMusicVolume(float volume) {
    _musicVolume = volume;
}

float ECS::Components::Volume::getSfxVolume() const {
    return _sfxVolume;
}

void ECS::Components::Volume::setSfxVolume(float volume) {
    _sfxVolume = volume;
}
