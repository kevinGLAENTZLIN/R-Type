#pragma once

#include "../System/System.hpp"

#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Velocity/Velocity.hh"

namespace ECS {
    namespace Systems {

        class UpdateVelocityPataPata : public System {
        public:
            UpdateVelocityPataPata() = default;
            ~UpdateVelocityPataPata() = default;

            void update(
                ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocities,
                std::vector<std::size_t> pataPatas, float timeElapsed));
        };
    }
}
