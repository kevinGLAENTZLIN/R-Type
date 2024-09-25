/*
** EPITECH PROJECT, 2024
** SystemVelocity.hh
** File description:
** SystemVelocity class
*/
#pragma once

#include <vector>
#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Position/Position.hpp"
#include "../../Component/Velocity/Velocity.hh"

namespace ECS {
    namespace Systems {
        
        class SystemVelocity : public System {
        public:
            SystemVelocity() = default;
            ~SystemVelocity() = default;
        
            void update(ComponentManager::SparseArray<Components::Position> &positions,
                        ComponentManager::SparseArray<Components::Velocity> &velocities,
                        std::vector<std::size_t> &entities);
        };
    }
}
