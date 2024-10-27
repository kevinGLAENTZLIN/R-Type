/*
** EPITECH PROJECT, 2024
** SystemVelocity.cpp
** File description:
** SystemVelocity cpp
*/
#include "Velocity.hpp"

void ECS::Systems::SystemVelocity::update(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Velocity> &velocities,
    std::vector<std::size_t> &entities)
{
    for (auto &entity : entities) {
        auto &position = positions[entity].value();
        auto &velocity = velocities[entity].value();
        position.setX(position.getX() + velocity.getX());
        position.setY(position.getY() + velocity.getY());
        velocity.setX(0.); //? Temp -> parallax issue
        velocity.setY(0.); //? Temp -> parallax issue
    }
}
