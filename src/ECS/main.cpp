/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** main to test ECS Core
*/
#include "Core/Core.hpp"
#include "Component/Position/Position.hpp"
#include "Component/Velocity/Velocity.hh"
#include "System/Velocity/Velocity.hpp"

std::size_t ECS::ComponentManager::ComponentTypeRegistry::nextTypeIndex = 0;

int main(void)
{
    ECS::Core::Core core;

    core.registerComponent<ECS::Components::Position>();
    core.registerComponent<ECS::Components::Velocity>();

    auto velocitySystem = core.registerSystem<ECS::Systems::SystemVelocity>();

    Signature velocitySystemSignature;
    velocitySystemSignature.set(1);
    velocitySystemSignature.set(2);
    core.setSystemSignature<ECS::Systems::SystemVelocity>(velocitySystemSignature);

    std::cout << "-----------------------------------\n";

    std::size_t entity1 = core.createEntity();
    std::size_t entity2 = core.createEntity();

    std::cout << "Entity 1: " << entity1 << std::endl;
    std::cout << "Entity 2: " << entity2 << std::endl;
    
    core.addComponent(entity1, ECS::Components::Position{4.4f, 5.7f});
    core.addComponent(entity2, ECS::Components::Position{84.0f, 42.0f});
    core.addComponent(entity2, ECS::Components::Velocity{0.5f, 0.5f});

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "entity1 signature:" << core.getSignature(entity1) << std::endl;
    std::cout << "entity2 signature:" << core.getSignature(entity2) << std::endl;

    std::cout << "-----------------------------------\n";
    std::cout << "Initial Entity 1 Position: ";
    std::cout << core.getComponent<ECS::Components::Position>(entity1) << std::endl;
    std::cout << "Initial Entity 2 Position: ";
    std::cout << core.getComponent<ECS::Components::Position>(entity2) << std::endl;
    std::cout << "Initial Entity 2 Velocity: ";
    std::cout << core.getComponent<ECS::Components::Velocity>(entity2) << std::endl;

    std::cout << "-----------------------------------\n";

    std::vector<std::size_t> entities = {entity1, entity2};
    velocitySystem->update(core.getComponents<ECS::Components::Position>(),
                           core.getComponents<ECS::Components::Velocity>(),
                           entities);

    std::cout << "Updated Entity 1 Position: ";
    std::cout << core.getComponent<ECS::Components::Position>(entity1) << std::endl;
    std::cout << "Updated Entity 2 Position: ";
    std::cout << core.getComponent<ECS::Components::Position>(entity2) << std::endl;

    return 0;
}
