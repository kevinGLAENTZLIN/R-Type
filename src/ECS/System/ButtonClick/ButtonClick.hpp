/*
** EPITECH PROJECT, 2024
** R-Type - System: buttonClick
** File description:
** Handles the check when clicking a button
*/
#pragma once

#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <vector>

#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Position/Position.hpp"
#include "../../Component/Hitbox/Hitbox.hh"

namespace ECS {
    namespace Systems {

        class ButtonClick : public System {
        public:
            ButtonClick() = default;
            ~ButtonClick() = default;

            void onClick(
                ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
                ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> & hitboxes,
                const sf::Vector2i & mousePos,
                const std::vector<std::size_t> & entities) const {
                std::size_t entity = 0;
                
                for (std::size_t index = 0; index < entities.size(); index++) {
                    entity = entities[index];
                    if (mousePos.x > positions[entity]->getX() &&
                        mousePos.x < positions[entity]->getX() + hitboxes[entity]->getWidth() &&
                        mousePos.y > positions[entity]->getY() &&
                        mousePos.y < positions[entity]->getY() + hitboxes[entity]->getHeight())
                        std::cout << "OUAIS LE BOUTON DE ZINZIN" << std::endl;
                }
/*                std::cout << "clicked outside button" << std::endl;
                std::cout << "______________________" << std::endl;
                std::cout << "mouse X: " << mousePos.x << std::endl;
                std::cout << "mouse Y: " << mousePos.y << std::endl;
                std::cout << "button left X: " << positions[entity]->getX() << std::endl;
                std::cout << "button right X: " << positions[entity]->getX() + hitboxes[entity]->getWidth() << std::endl;
                std::cout << "button top Y: " << positions[entity]->getY() << std::endl;
                std::cout << "button bottom Y: " << positions[entity]->getY() + hitboxes[entity]->getWidth() << std::endl;*/
            };
        };
    }
}
