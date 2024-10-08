/*
** EPITECH PROJECT, 2024
** SystemRender3D.hh
** File description:
** SystemRender3D class
*/
#pragma once

#include <vector>
#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Position/Position.hpp"
#include "../../Component/Render3D/Render3D.hh"
#include "../../RessourcePool/RessourcePool.hh"
#include "../../Utils/Utils.hh"

namespace ECS {
    namespace Systems {

        class SystemRender3D: public System {
        public:
            SystemRender3D() = default;
            ~SystemRender3D() = default;

            void update(ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                        ECS::ComponentManager::SparseArray<ECS::Components::Render3D> &renders,
                        std::vector<std::size_t> &entities,
                        ECS::RessourcePool &ressourcePool,
                        raylib::Camera3D &camera);;
        };
    }
}
