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
            void isHit(
                ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
                ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> & hitboxes,
                std::vector<std::size_t> & entities);

            /**
            * @brief Static function to handle projectile collisions with other entities.
            *
            * This function checks for collisions between projectiles and other entities,
            * ensuring that projectile hit detection is managed independently from regular entity collisions.
            *
            * @param positions SparseArray of Position components of the entities.
            * @param hitboxes SparseArray of Hitbox components of the entities.
            * @param projectiles Vector of projectile entity IDs to check for collisions.
            * @param entities Vector of other entity IDs to check for collisions with the projectiles.
            * @return void.
            */
            static void projectileIsHit(
                ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
                ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> & hitboxes,
                std::vector<std::size_t> & projectiles, std::vector<std::size_t> & entities);
        };
    }
}
