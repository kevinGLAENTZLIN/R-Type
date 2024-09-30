/*
** EPITECH PROJECT, 2024
** R-Type - Components : Volume
** File description:
** Volume Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Volume {
        public:
            Volume(float masterVolume = 1.0f, float musicVolume = 1.0f, float sfxVolume = 1.0f);
            ~Volume() = default;

            float getMasterVolume() const;
            void setMasterVolume(float volume);
            float getMusicVolume() const;
            void setMusicVolume(float volume);
            float getSfxVolume() const;
            void setSfxVolume(float volume);

        private:
            float _masterVolume;
            float _musicVolume;
            float _sfxVolume;
        };
    }
}
