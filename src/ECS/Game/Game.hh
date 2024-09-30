/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Game class is the main class to game.
** It will handle game and state.
*/

#pragma once

#include "../Core/Core.hpp"
#include "../Component/Health/Health.hh"
#include "../Component/Position/Position.hpp"
#include "../Component/Velocity/Velocity.hh"
#include "../Component/Hitbox/Hitbox.hh"
#include "../Component/Text/Text.hh"

#include "../System/SystemManager/SystemManager.hpp"

#include "../System/Velocity/Velocity.hpp"
#include "../System/Collision/Collision.hh"
#include "../Entity/Button/Button.hh"

#include "raylib-cpp.hpp"

#include <memory>

namespace Rtype {
    class Game {
    public:
        Game();
        ~Game();

        void run();

    private:
        void update();
        void render();
        bool _isRunning;
        std::unique_ptr<ECS::Core::Core> _core;
        raylib::Window _window;

    };
};
