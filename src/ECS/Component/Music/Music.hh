/*
** EPITECH PROJECT, 2024
** R-Type - Components : Music
** File description:
** Music Component
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
namespace ECS {
    namespace Components {

        class Musica {
        public:
            /**
            * @brief Constructor to Music component.
            *
            * Constructor for the music component, which  represent the
            * music of the entities in the video game,
            *
            * @param const std::string &filePath : the path to the music file.
            * @return void.
            */
            Musica(const std::string &filePath);

            /**
            * @brief Destructor to Music component.
            *
            * Destructor for the music component.
            *
            * @return void.
            */
            ~Musica() = default;

            /**
            * @brief Play the music.
            *
            * Play the music from the beginning.
            *
            * @return void.
            */
            void play();

            /**
            * @brief Play the music from a specific time.
            *
            * Play the music from a specific time.
            *
            * @param float startTime : the time to start the music from.
            * @return void.
            */
            void playFrom(float startTime);

            /**
            * @brief Stop the music.
            *
            * Stop the music.
            *
            * @return void.
            */
            void stop();

            /**
            * @brief Pause the music.
            *
            * Pause the music.
            *
            * @return void.
            */
            void pause();

            /**
            * @brief Resume the music.
            *
            * Resume the music.
            *
            * @return void.
            */
            void resume();

            /**
            * @brief Update the music.
            *
            * Update the music.
            *
            * @return void.
            */
            void update();

            /**
            * @brief Get the time played.
            *
            * Get the time played.
            *
            * @return float : the time played.
            */
            float getTimePlayed() const;

            /**
            * @brief set the volume of the music.
            *
            * Set the volume of the music.
            *
            * @param float volume : the volume to set.
            * @return void.
            */
            void setVolume(float volume);

            /**
            * @brief Get the volume of the music.
            *
            * Get the volume of the music.
            *
            * @return float : the volume of the music.
            */
            float getVolume() const;

        private:
            Music _musicStream;
            bool _isPaused;
            float _volume;
        };

    }
}
