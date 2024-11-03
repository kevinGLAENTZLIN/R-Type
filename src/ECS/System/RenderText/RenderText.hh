/*
** EPITECH PROJECT, 2024
** RenderText class.hh
** File description:
** RenderText class
*/

#pragma once

#include "../System/System.hpp"
#include "../../Component/Text/Text.hh"
#include "../../Component/Position/Position.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"

namespace ECS {
    namespace Systems {
    class RenderTextSystem : public System {
    public:
    /**
    * @brief Render the text
    * @param ECS::ComponentManager::SparseArray<ECS::Components::Text> &text
    * @param ECS::ComponentManager::SparseArray<ECS::Components::Position> &position
    * @param std::vector<std::size_t> &entities
    * @return void
    */
    void update(ECS::ComponentManager::SparseArray<ECS::Components::Text> &texts,
                        ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                        const std::vector<std::size_t> &entities);
        };
    };
}
