/*
** EPITECH PROJECT, 2024
** R-Type - Components : Sound
** File description:
** Sound Component
*/

#pragma once
#include "raylib-cpp.hpp"
#include <string>

namespace ECS {
    namespace Components {

        class SoundEffect {
        public:
            SoundEffect(const std::string &filePath);
            ~SoundEffect() = default;

            void play();
            void stop();
            void setVolume(float volume);
            float getVolume() const;

        private:
            Sound _soundEffect;
            float _volume;
        };
    }
}
