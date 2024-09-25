/*
** EPITECH PROJECT, 2024
** SystemVelocity.cpp
** File description:
** SystemVelocity cpp
*/

#include "SystemVelocity.hpp"

void Systems::SystemVelocity::update(
    ComponentManager::SparseArray<Components::Position> &positions,
    ComponentManager::SparseArray<Components::Velocity> &velocities,
    std::vector<std::size_t> &entities)
{
    for (auto &entity : entities) {
        if (positions[entity].has_value() && velocities[entity].has_value()) {
            auto &position = positions[entity].value();
            auto &velocity = velocities[entity].value();
            position.setX(position.getX() + velocity.getX());
            position.setY(position.getY() + velocity.getY());
        }
    }
}
