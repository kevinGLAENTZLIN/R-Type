/*
** EPITECH PROJECT, 2024
** R-Type - Systems : InputUpdates
** File description:
** Updates information based on the inputs
*/
#include "InputUpdates.hh"
#include "../../Component/Input/enumInput.hpp"

void ECS::Systems::InputUpdates::updateInputs(
    const std::vector<std::size_t> & inputs,
    ECS::ComponentManager::SparseArray<ECS::Components::Input> & inputComponents,
    std::vector<std::size_t> entities)
{
    for (std::size_t i = 0; i < entities.size(); i++)
        inputComponents[entities[i]]->setInputs(inputs);
}

void ECS::Systems::InputUpdates::updateInputedVelocity(
    ECS::ComponentManager::SparseArray<ECS::Components::Input> & inputs,
    ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocities,
    std::vector<std::size_t> entities)
{
    float velX = 0;
    float velY = 0;

    for (std::size_t i = 0; i < entities.size(); i++) {
        if (inputs[entities[i]]->contains(ECS::Components::RIGHT))
            velX += 2;
        if (inputs[entities[i]]->contains(ECS::Components::UP))
            velY -= 2;
        if (inputs[entities[i]]->contains(ECS::Components::LEFT))
            velX -= 2;
        if (inputs[entities[i]]->contains(ECS::Components::DOWN))
            velY += 2;
        velocities[entities[i]]->setVelPair(std::make_pair(velX, velY));
    }
    inputs.clear();
}
