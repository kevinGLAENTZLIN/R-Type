/*
** EPITECH PROJECT, 2024
** SystemBackground.hh
** File description:
** SystemBackground class
*/
#pragma once

#include <vector>
#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Position/Position.hpp"
#include "../../Component/Background/Background.hpp"
#include "../../RessourcePool/RessourcePool.hh"
#include "../../Utils/Utils.hh"

namespace ECS {
    namespace Systems {

        class SystemBackground: public System {
        public:
            SystemBackground() = default;
            ~SystemBackground() = default;

            /**
            * @brief Update the background of the entities
            *
            * @param ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions
            * @param ECS::ComponentManager::SparseArray<ECS::Components::Background> &backgrounds
            * @param std::vector<std::size_t> &entities
            * @return void
            */
            void update(ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                        ECS::ComponentManager::SparseArray<ECS::Components::Background> &backgrounds,
                        std::vector<std::size_t> &entities);
        };
    }
}
