#pragma once

#include "../System/System.hpp"

#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/AI/AI.hh"
#include "../../Component/Pod/Pod.hh"
#include "../../Component/Position/Position.hpp"

namespace ECS {
    namespace Systems {

        class AIFiringProjectile : public System {
        public:
            /**
            * @brief AI firing projectile system
            *
            * @param ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs
            * @param ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions
            * @param std::vector<std::size_t> & entities
            * @return void
            */
            std::vector<std::size_t> aiFiringBydoShots(
                ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs,
                ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
                std::vector<std::size_t> & entities);

            /**
            * @brief AI firing projectile system
            *
            * @param ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs
            * @param std::vector<std::size_t> & entities
            * @return void
            */
            std::vector<std::size_t> aiFiringHomingShots(
                ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs,
                std::vector<std::size_t> & entities);

            /**
            * @brief AI firing projectile system
            *
            * @param ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs
            * @param std::vector<std::size_t> & entities
            * @return void
            */
            std::vector<std::size_t> podFiringShots(
                ECS::ComponentManager::SparseArray<ECS::Components::Pod> & pods,
                std::vector<std::size_t> & entities);
        };
    }
}
