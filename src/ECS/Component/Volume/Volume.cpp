/*
** EPITECH PROJECT, 2024
** R-Type - Components : Volume
** File description:
** Volume Component
*/

#include "Volume.hh"

/**
 * @brief Constructor of Volume component.
 *
 * @tparam float masterVolume, float musicVolume, float sfxVolume.
 * @return void.
 */
ECS::Components::Volume::Volume(float masterVolume, float musicVolume, float sfxVolume):
    _masterVolume(masterVolume), _musicVolume(musicVolume), _sfxVolume(sfxVolume)
{}

/**
 * @brief Getter for _masterVolume.
 *
 * @tparam void.
 * @return float _masterVolume.
 */
float ECS::Components::Volume::getMasterVolume() const {
    return _masterVolume;
}

/**
 * @brief Setter for _masterVolume.
 *
 * @param float volume: The new value for the master volume.
 * @return void.
 */
void ECS::Components::Volume::setMasterVolume(float volume) {
    _masterVolume = volume;
}

/**
 * @brief Getter for _musicVolume.
 *
 * @tparam void.
 * @return float _musicVolume.
 */
float ECS::Components::Volume::getMusicVolume() const {
    return _musicVolume;
}

/**
 * @brief Setter for _musicVolume.
 *
 * @param float volume: The new value for the music volume.
 * @return void.
 */
void ECS::Components::Volume::setMusicVolume(float volume) {
    _musicVolume = volume;
}

/**
 * @brief Getter for _sfxVolume.
 *
 * @tparam void.
 * @return float _sfxVolume.
 */
float ECS::Components::Volume::getSfxVolume() const {
    return _sfxVolume;
}

/**
 * @brief Setter for _sfxVolume.
 *
 * @param float volume: The new value for the sound effects volume.
 * @return void.
 */
void ECS::Components::Volume::setSfxVolume(float volume) {
    _sfxVolume = volume;
}
