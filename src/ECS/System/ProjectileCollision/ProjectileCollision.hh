/*
** EPITECH PROJECT, 2024
** R-Type - System : Hitbox
** File description:
** System hitbox class
*/

#pragma once

#include <vector>
#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Position/Position.hpp"
#include "../../Component/Hitbox/Hitbox.hh"
#include "../../Component/Projectile/Projectile.hh"

namespace ECS {
    namespace Systems {

        class ProjectileCollision : public System {
        public:
            ProjectileCollision() = default;
            ~ProjectileCollision() = default;

            void projectileIsHit(
                ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
                ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> & hitboxes,
                ECS::ComponentManager::SparseArray<ECS::Components::Projectile> & projectiles,
                std::vector<std::size_t> & projectileEntities, std::vector<std::size_t> & entities);

            bool checkCollision2(
                const ECS::Components::Position &posA,
                const ECS::Components::Hitbox &hitboxA,
                const ECS::Components::Position &posB,
                const ECS::Components::Hitbox &hitboxB);
        };
    }
}
