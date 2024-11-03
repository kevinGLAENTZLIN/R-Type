/*
** EPITECH PROJECT, 2024
** R-Type - Systems : AI movement system
** File description:
** AI movement System
*/
#pragma once

#include "../System/System.hpp"

#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Velocity/Velocity.hh"
#include "../../Component/Position/Position.hpp"
#include "../../Component/AI/AI.hh"
#include <map>
#include <cmath>

#if defined(_WIN32)
    #define M_PI 3.14159265358979323846
#endif

namespace ECS {
    namespace Systems {
        class UpdateVelocityAI : public System {
        public:
            UpdateVelocityAI() = default;
            ~UpdateVelocityAI() = default;

            /**
            * @brief This function updates the position of entities based on their velocity.
            *
            * @param velocities SparseArray of Velocity components where the velocities of entities are stored.
            * @param positions SparseArray of Position components where the positions of entities are stored.
            * @return void.
            */
            void update(
                ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocities,
                ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
                ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs,
                std::vector<std::size_t> entities,
                const std::map<int, std::size_t> & serverToLocalPlayersId) const;
        };
    }
}
