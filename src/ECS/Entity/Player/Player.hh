/*
** EPITECH PROJECT, 2024
** Player.hh
** File description:
** Player class
*/
#include <cstddef>

#include <iostream>

namespace ECS {
    namespace Entities {
        class Player {

        public:
            Player(std::size_t id);
            ~Player() = default;

            std::size_t getId() const;

        private:
            std::size_t _id;
        };
    }
}
