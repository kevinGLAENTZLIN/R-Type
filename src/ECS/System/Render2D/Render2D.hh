/*
** EPITECH PROJECT, 2024
** SystemRender2D.hh
** File description:
** SystemRender2D class
*/
#pragma once

#include <vector>
#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Position/Position.hpp"
#include "../../Component/Render2D/Render2D.hh"
#include "../../RessourcePool/RessourcePool.hh"
#include "../../Utils/Utils.hh"

namespace ECS {
    namespace Systems {

        class SystemRender2D: public System {
        public:
            SystemRender2D() = default;
            ~SystemRender2D() = default;

            void update(ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                        ECS::ComponentManager::SparseArray<ECS::Components::Render2D> &renders,
                        std::vector<std::size_t> &entities,
                        ECS::RessourcePool &ressourcePool
                        );
        };
    }
}
