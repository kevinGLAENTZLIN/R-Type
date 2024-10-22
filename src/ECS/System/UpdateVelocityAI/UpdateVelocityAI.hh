/*
** EPITECH PROJECT, 2024
** R-Type - Systems : AI movement system
** File description:
** AI movement System
*/
#pragma once
#include <cmath>
#include "../System/System.hpp"

#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Velocity/Velocity.hh"
#include "../../Component/Position/Position.hpp"
#include "../../Component/AI/AI.hh"
#include <map>
#include <cmath>

namespace ECS {
    namespace Systems {

        class UpdateVelocityAI : public System {
        public:
            UpdateVelocityAI() = default;
            ~UpdateVelocityAI() = default;

            void update(
                ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocities,
                ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
                ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs,
                std::vector<std::size_t> entities,
                const std::map<int, std::size_t> & serverToLocalPlayersId) const;

        private:
            float getDistance(
                const std::optional<ECS::Components::Position> & pos1,
                const std::optional<ECS::Components::Position> & pos2) const;
            
            std::size_t getClosestPlayer(
                ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
                std::size_t ai, std::map<int, std::size_t> serverToLocalPlayersId) const;
        };
    }
}
