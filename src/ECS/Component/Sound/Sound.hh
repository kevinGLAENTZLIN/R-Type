/*
** EPITECH PROJECT, 2024
** R-Type - Components : Sound
** File description:
** Sound Component
*/

#pragma once
#if defined(_WIN32)
	#define NOGDI
	#define NOUSER
#endif

#include "raylib-cpp.hpp"

#if defined(_WIN32)
	#undef near
	#undef far
#endif

#include <string>

namespace ECS {
    namespace Components {

        class SoundEffect {
        public:
            /**
            * @brief Constructor of Sound component.
            *
            * @tparam std::string &filePath : path to the sound file.
            * @return void.
            */
            SoundEffect(const std::string &filePath);

            /**
            * @brief Destructor of Sound component.
            *
            * @return void.
            */
            ~SoundEffect() = default;

            /**
            * @brief Play the sound.
            *
            * @return void.
            */
            void play();

            /**
            * @brief Stop the sound.
            *
            * @return void.
            */
            void stop();

            /**
            * @brief Set the volume of the sound.
            *
            * @param float volume : volume of the sound.
            * @return void.
            */
            void setVolume(float volume);

            /**
            * @brief Get the volume of the sound.
            *
            * @return float : volume of the sound.
            */
            float getVolume() const;

        private:
            Sound _soundEffect;
            float _volume;
        };
    }
}
