/*
** EPITECH PROJECT, 2024
** RenderText class.hh
** File description:
** RenderButton class
*/

#pragma once

#include "../System/System.hpp"
#include "../../Component/Text/Text.hh"
#include "../../Component/Position/Position.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Button/Button.hh"

namespace ECS {
    namespace Systems {
        class RenderButtonSystem : public System {
            public:
                void update(ECS::ComponentManager::SparseArray<ECS::Components::Button> &buttons,
                            ECS::ComponentManager::SparseArray<ECS::Components::Text> &texts,
                            ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                            const std::vector<std::size_t> &entities);
        };
    }
};