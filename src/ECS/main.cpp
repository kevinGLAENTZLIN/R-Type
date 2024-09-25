/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** main to test ECS Core
*/
#include "Component/Health/Health.hh"
#include "Core/Core.hpp"
#include "Component/Position/Position.hpp"
#include "Component/Velocity/Velocity.hh"
#include "Component/Health/Health.hh"
#include "System/Velocity/Velocity.hpp"

std::size_t ECS::ComponentManager::ComponentTypeRegistry::nextTypeIndex = 0;

int main(void)
{
    ECS::Core::Core core;

    core.registerComponent<ECS::Components::Position>();
    core.registerComponent<ECS::Components::Velocity>();
    core.registerComponent<ECS::Components::Health>();

    auto velocitySystem = core.registerSystem<ECS::Systems::SystemVelocity>();

    Signature velocitySystemSignature;
    velocitySystemSignature.set(ECS::ComponentManager::ComponentTypeRegistry::getTypeId<ECS::Components::Position>());
    velocitySystemSignature.set(ECS::ComponentManager::ComponentTypeRegistry::getTypeId<ECS::Components::Velocity>());
    velocitySystemSignature.set(ECS::ComponentManager::ComponentTypeRegistry::getTypeId<ECS::Components::Health>());
    core.setSystemSignature<ECS::Systems::SystemVelocity>(velocitySystemSignature);

    std::cout << "-----------------------------------\n";

    std::size_t entity1 = core.createEntity();
    std::size_t entity2 = core.createEntity();

    std::cout << "Entity 1: " << entity1 << std::endl;
    std::cout << "Entity 2: " << entity2 << std::endl;
    
    core.addComponent(entity1, ECS::Components::Position{4.4f, 5.7f});
    core.addComponent(entity2, ECS::Components::Position{84.0f, 42.0f});
    core.addComponent(entity2, ECS::Components::Velocity{0.5f, 0.5f});

    core.addComponent(entity1, ECS::Components::Position{4.4f, 5.7f});
    core.addComponent(entity1, ECS::Components::Velocity{49.0f, 90.0f});
    core.addComponent(entity2, ECS::Components::Position{84.0f, 42.0f});
    core.addComponent(entity2, ECS::Components::Velocity{0.5f, 0.5f});

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "entity1 signature:" << core.getSignature(entity1) << std::endl;
    std::cout << "entity2 signature:" << core.getSignature(entity2) << std::endl;

    std::cout << "-----------------------------------\n";

    std::cout << "Signature system: " << velocitySystemSignature << std::endl;

    std::cout << "-----------------------------------\n";
    std::cout << "Initial Entity 1 Position: ";
    std::cout << core.getComponent<ECS::Components::Position>(entity1) << std::endl;
    std::cout << "-----------------------------------\n";
    std::cout << "Initial Entity 2 Position: ";
    std::cout << core.getComponent<ECS::Components::Position>(entity2) << std::endl;
    std::cout << "Initial Entity 2 Velocity: ";
    std::cout << core.getComponent<ECS::Components::Velocity>(entity2) << std::endl;

    std::cout << "Updated Entity 1 Position: ";
    std::cout << core.getComponent<ECS::Components::Position>(entity1) << std::endl;
    std::cout << "Updated Entity 2 Position: ";
    std::cout << core.getComponent<ECS::Components::Position>(entity2) << std::endl;

    return 0;
}
