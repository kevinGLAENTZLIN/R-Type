#pragma once

#include <cmath>
#include "../System/System.hpp"

#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Velocity/Velocity.hh"
#include "../../Component/Position/Position.hpp"

namespace ECS {
    namespace Systems {

        /**
        * @brief System that updates the velocity of "PataPata" entities.
        *
        * The UpdateVelocityPataPata class is responsible for updating the velocity of entities
        * that exhibit sinusoidal movement (PataPatas).
        */
        class UpdateVelocityPataPata : public System {
        public:
            /**
            * @brief Default constructor for UpdateVelocityPataPata.
            *
            * Initializes a new instance of the UpdateVelocityPataPata system.
            */
            UpdateVelocityPataPata() = default;

            /**
            * @brief Default destructor for UpdateVelocityPataPata.
            */
            ~UpdateVelocityPataPata() = default;

            /**
            * @brief Updates the velocity of PataPata entities.
            *
            * For each entity in the `pataPatas` list, this method updates its velocity
            * based on a sinusoidal function for the Y-velocity. The X-velocity is set to a constant value.
            *
            * @param velocities SparseArray of Velocity components, where velocities of entities are stored.
            * @param positions SparseArray of Position components, where positions of entities are stored.
            * @param pataPatas Vector of entity indices representing the PataPata entities to update.
            * @return void.
            */
            void update(
                ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocities,
                ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
                std::vector<std::size_t> pataPatas);
        };
    }
}