/*
** EPITECH PROJECT, 2024
** R-Type - enumInput
** File description:
** enumInput
*/
#pragma once

#include <iostream>
#include "raylib-cpp.hpp"

namespace ECS {
    namespace Components {

        typedef enum enumInput_e {
            MENU = 0,
            RIGHT = 1,
            UP = 2,
            LEFT = 3,
            DOWN = 4,
            SPACE = 5
        } enumInput_t;
    }
}
