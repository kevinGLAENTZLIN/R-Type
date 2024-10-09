/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Game class is the main class to game.
** It will handle game and state.
*/

#pragma once

#include "../Core/Core.hpp"

#include "../Entity/Button/Button.hh"

#include "../Component/Health/Health.hh"
#include "../Component/Position/Position.hpp"
#include "../Component/Velocity/Velocity.hh"
#include "../Component/Hitbox/Hitbox.hh"
#include "../Component/Text/Text.hh"
#include "../Component/Input/Input.hh"
#include "../Component/Projectile/Projectile.hh"
#include "../Component/Background/Background.hpp"
#include "../Component/Patapata/Patapata.hpp"

#include "../System/SystemManager/SystemManager.hpp"

#include "../System/Velocity/Velocity.hpp"
#include "../System/Collision/Collision.hh"
#include "../System/ProjectileCollision/ProjectileCollision.hh"
#include "../System/InputUpdates/InputUpdates.hh"
#include "../System/Render3D/Render3D.hh"
#include "../System/Render2D/Render2D.hh"

#include "../RessourcePool/RessourcePool.hh"
#include "raylib-cpp.hpp"

#include <memory>

namespace Rtype {
    class Game {
    public:
        Game();
        ~Game();

        void run();

    private:
        ECS::RessourcePool _ressourcePool;
        void createProjectile(std::size_t entityID);
        void destroyProjectile(std::size_t entityID);
        void update();
        void render();
        bool _isRunning;
        std::unique_ptr<ECS::Core::Core> _core;
        raylib::Window _window;
        raylib::Camera3D _camera;
    };
};
