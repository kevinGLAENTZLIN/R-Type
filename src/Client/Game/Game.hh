/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Game class is the main class to game.
** It will handle game and state.
*/

#pragma once

#include "../../ECS/Core/Core.hpp"

#include "../../ECS/Entity/Button/Button.hh"

#include "../../ECS/Component/Health/Health.hh"
#include "../../ECS/Component/Position/Position.hpp"
#include "../../ECS/Component/Velocity/Velocity.hh"
#include "../../ECS/Component/Hitbox/Hitbox.hh"
#include "../../ECS/Component/Text/Text.hh"
#include "../../ECS/Component/Input/Input.hh"
#include "../../ECS/Component/Projectile/Projectile.hh"
#include "../../ECS/Component/Background/Background.hpp"
#include "../../ECS/Component/Patapata/Patapata.hpp"

#include "../../ECS/System/SystemManager/SystemManager.hpp"

#include "../../ECS/System/Velocity/Velocity.hpp"
#include "../../ECS/System/Collision/Collision.hh"
#include "../../ECS/System/ProjectileCollision/ProjectileCollision.hh"
#include "../../ECS/System/InputUpdates/InputUpdates.hh"
#include "../../ECS/System/Render3D/Render3D.hh"
#include "../../ECS/System/Render2D/Render2D.hh"
#include "../../ECS/System/Background/Background.hh"

#include "../../ECS/System/UpdateVelocityPataPata/UpdateVelocityPataPata.hh"

#include "../../ECS/RessourcePool/RessourcePool.hh"

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
        void createBackgroundLayers(float speed, std::string modelPath);
        void update();
        void render();
        bool _isRunning;
        std::unique_ptr<ECS::Core::Core> _core;
        raylib::Window _window;
        raylib::Camera3D _camera;
    };
};
