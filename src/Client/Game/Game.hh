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
#include "../../ECS/Component/AI/AI.hh"

#include "../../ECS/System/SystemManager/SystemManager.hpp"

#include "../../ECS/System/Velocity/Velocity.hpp"
#include "../../ECS/System/Collision/Collision.hh"
#include "../../ECS/System/ProjectileCollision/ProjectileCollision.hh"
#include "../../ECS/System/InputUpdates/InputUpdates.hh"
#include "../../ECS/System/Render3D/Render3D.hh"
#include "../../ECS/System/Render2D/Render2D.hh"
#include "../../ECS/System/Background/Background.hh"
#include "../../ECS/System/UpdateVelocityAI/UpdateVelocityAI.hh"

#include "../../ECS/RessourcePool/RessourcePool.hh"

#include "../../Utils/enemiesTypeEnum.hpp"
#include <cstddef>
#include <utility>

namespace Rtype {
    class Game {
    public:
        Game();
        ~Game();

        void run();
        std::size_t createPlayer(int id, float pos_x, float pos_y);
        void createOtherPlayer(int id, float pos_x, float pos_y);
        std::size_t createEnemy(enemiesTypeEnum_t enemyType, float pos_x, float pos_y);
        void movePlayer(int id, float x, float y);
        void createEnemyProjectile(int id);

    private:
        void createPlayerProjectile(std::size_t entityID);
        void destroyProjectile(std::size_t entityID);
        void createBackgroundLayers(float speed, std::string modelPath);
        void update();
        void render();
        bool _isRunning;
        std::unique_ptr<ECS::Core::Core> _core;
        raylib::Window _window;
        raylib::Camera3D _camera;
        std::map<int, std::size_t> _mapID;
        ECS::RessourcePool _ressourcePool;
    };
};
