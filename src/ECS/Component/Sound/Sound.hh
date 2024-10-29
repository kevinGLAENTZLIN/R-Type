/*
** EPITECH PROJECT, 2024
** R-Type - Components : Sound
** File description:
** Sound Component
*/

#pragma once
#if defined(_WIN32)           
	#define NOGDI             // All GDI defines and routines
	#define NOUSER            // All USER defines and routines
#endif

#include "raylib-cpp.hpp"

#if defined(_WIN32)           // raylib uses these names as function parameters
	#undef near
	#undef far
#endif

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
