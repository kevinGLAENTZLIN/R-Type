/*
** EPITECH PROJECT, 2024
** R-Type - Components : Pod
** File description:
** Pod Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Pod {
        public:
            Pod(std::size_t player = 10000);

            std::size_t getPlayer();
            void setPlayer(std::size_t player);

            std::size_t getLevel();
            void setLevel(std::size_t level);

            bool isUp();
            void setIsUp(bool isUp);

        private:
            std::size_t _player;
            std::size_t _level;
            bool _isUp;
        };
    }
}
