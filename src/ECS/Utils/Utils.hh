/*
** EPITECH PROJECT, 2024
** Utils.hh
** File description:
** Utils class
*/

#pragma once
#include <iostream>

#include "../Component/Position/Position.hpp"
#include "../Component/Hitbox/Hitbox.hh"

namespace ECS {
    class Utils {
        static bool checkCollision(
            const ECS::Components::Position &posA,
            const ECS::Components::Hitbox &hitboxA,
            const ECS::Components::Position &posB,
            const ECS::Components::Hitbox &hitboxB);

    };
}
