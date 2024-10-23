/*
** EPITECH PROJECT, 2024
** R-Type - Components : Music
** File description:
** Music Component
*/

#pragma once

#include "raylib-cpp.hpp"

namespace ECS {
    namespace Components {

        class Musica {
        public:
            Musica(const std::string &filePath);
            ~Musica() = default;

            void play();
            void playFrom(float startTime);
            void stop();
            void pause();
            void resume();
            void update();
            float getTimePlayed() const;

        private:
            Music _musicStream;
            bool _isPaused;
        };

    }
}
