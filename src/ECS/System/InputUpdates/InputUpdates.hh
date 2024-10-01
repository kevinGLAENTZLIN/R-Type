/*
** EPITECH PROJECT, 2024
** R-Type - Systems : InputUpdates
** File description:
** Update informations based on inputs.
*/
#pragma once

#include "../System/System.hpp"

#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Input/Input.hh"
#include "../../Component/Velocity/Velocity.hh"
#include <cstddef>

namespace ECS {
    namespace Systems {

        class InputUpdates : public System{
        public:
            InputUpdates() = default;
            ~InputUpdates() = default;

            std::size_t updateInputs(const std::vector<std::size_t> & inputs,
                              ECS::ComponentManager::SparseArray<ECS::Components::Input> & inputComponents,
                              std::vector<std::size_t> entities);

            void updateInputedVelocity(
                ECS::ComponentManager::SparseArray<ECS::Components::Input> & inputs,
                ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocitites,
                std::vector<std::size_t> entities);


        };
    }
}
