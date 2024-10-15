#pragma once

#include <cmath>
#include "../System/System.hpp"

#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Velocity/Velocity.hh"
#include "../../Component/Position/Position.hpp"

namespace ECS {
    namespace Systems {

        class UpdateVelocityPataPata : public System {
        public:
            UpdateVelocityPataPata() = default;
            ~UpdateVelocityPataPata() = default;

            void update(
                ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocities,
                ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
                std::vector<std::size_t> pataPatas);
        };
    }
}
