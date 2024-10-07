/*
** EPITECH PROJECT, 2024
** SystemRender.hh
** File description:
** SystemRender class
*/
#pragma once

#include <vector>
#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Position/Position.hpp"
#include "../../Component/Render/Render.hh"
#include "../../RessourcePool/RessourcePool.hh"
#include "../../Utils/Utils.hh"

namespace ECS {
    namespace Systems {

        class SystemRender: public System {
        public:
            SystemRender() = default;
            ~SystemRender() = default;

            void update(ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                        ECS::ComponentManager::SparseArray<ECS::Components::Render> &renders,
                        std::vector<std::size_t> &entities,
                        ECS::RessourcePool &ressourcePool);
        };
    }
}
