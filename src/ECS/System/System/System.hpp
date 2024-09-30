/*
** EPITECH PROJECT, 2024
** System.hpp
** File description:
** System class
*/
#pragma once

#include <cstddef>
#include <set>

namespace ECS {
    namespace Systems {

        class System {

        public:
            std::set<std::size_t> _entities;
        };
    }
}
