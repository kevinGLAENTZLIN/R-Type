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
#include "../../Component/Health/Health.hh"

namespace ECS {
    namespace Systems {

        /**
        * @class Collision
        * @brief Handles collision detection between entities.
        *
        * The Collision system is responsible for detecting collisions between entities
        * based on their position and hitbox components.
        */
        class Collision : public System {
        public:
            /**
            * @brief Default constructor for Collision system.
            */
            Collision() = default;

            /**
            * @brief Default destructor for Collision system.
            */
            ~Collision() = default;

            /**
            * @brief Detects collisions between all entities in the provided list.
            *
            * This function checks for collisions between pairs of entities by comparing
            * their positions and hitboxes.
            *
            * @param positions SparseArray of Position components of the entities.
            * @param hitboxes SparseArray of Hitbox components of the entities.
            * @param entities Vector of entity IDs to check for collisions.
            * @return void.
            */
            void playerIsHit(
                ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
                ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> & hitboxes,
                ECS::ComponentManager::SparseArray<ECS::Components::Health> & healths,
                std::size_t player, std::vector<std::size_t> & entities);
        };
    }
}
