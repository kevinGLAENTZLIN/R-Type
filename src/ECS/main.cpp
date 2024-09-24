/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** main to test ECS Core
*/

#include "Core/Core.hpp"
#include "Component/Position/Position.hpp"
#include "Component/Velocity/Velocity.hh"
#include "System/SystemVelocity/SystemVelocity.hpp"

int main(void)
{
    ECS::Core core;

    core.RegisterComponent<Components::Position>();
    core.RegisterComponent<Components::Velocity>();

    auto velocitySystem = core.RegisterSystem<SystemVelocity>();

    Signature velocitySystemSignature;
    velocitySystemSignature.set(1);
    velocitySystemSignature.set(2);
    core.SetSystemSignature<SystemVelocity>(velocitySystemSignature);

    std::cout << "-----------------------------------\n";

    std::size_t entity1 = core.CreateEntity();
    std::size_t entity2 = core.CreateEntity();

    std::cout << "Entity 1: " << entity1 << std::endl;
    std::cout << "Entity 2: " << entity2 << std::endl;

    core.GetComponent<Components::Position>(entity1) = Components::Position{1.0f, 2.0f};
    core.GetComponent<Components::Position>(entity2) = Components::Position{4.4f, 5.7f};
    core.GetComponent<Components::Velocity>(entity2) = Components::Velocity{0.5f, 0.5f};

    std::cout << "-----------------------------------\n";

    std::cout << "Initial Entity 1 Position: " << core.GetComponent<Components::Position>(entity1) << std::endl;
    std::cout << "Initial Entity 2 Position: " << core.GetComponent<Components::Position>(entity2) << std::endl;

    std::cout << "-----------------------------------\n";

    std::vector<std::size_t> entities = {entity1, entity2};
    velocitySystem->update(core.GetComponent<Components::Position>(), core.GetComponent<Components::Velocity>(), entities);

    std::cout << "Updated Entity 1 Position: " << core.GetComponent<Components::Position>(entity1) << std::endl;
    std::cout << "Updated Entity 2 Position: " << core.GetComponent<Components::Position>(entity2) << std::endl;

    return 0;
}
