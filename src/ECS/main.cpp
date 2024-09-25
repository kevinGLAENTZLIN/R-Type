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
#include "System/SystemVelocity/SystemVelocity.hpp"

std::size_t ComponentManager::ComponentTypeRegistry::nextTypeIndex = 0;

int main(void)
{
    ECS::Core core;

    core.RegisterComponent<Components::Position>();
    core.RegisterComponent<Components::Velocity>();
    core.RegisterComponent<Components::Health>();

    auto velocitySystem = core.RegisterSystem<Systems::SystemVelocity>();

    Signature velocitySystemSignature;
    velocitySystemSignature.set(ComponentManager::ComponentTypeRegistry::getTypeId<Components::Position>());
    velocitySystemSignature.set(ComponentManager::ComponentTypeRegistry::getTypeId<Components::Velocity>());
    velocitySystemSignature.set(ComponentManager::ComponentTypeRegistry::getTypeId<Components::Health>());
    core.SetSystemSignature<Systems::SystemVelocity>(velocitySystemSignature);

    std::cout << "-----------------------------------\n";

    std::size_t entity1 = core.createEntity();
    std::size_t entity2 = core.createEntity();

    std::cout << "Entity 1: " << entity1 << std::endl;
    std::cout << "Entity 2: " << entity2 << std::endl;

    core.AddComponent(entity1, Components::Position{4.4f, 5.7f});
    core.AddComponent(entity1, Components::Velocity{49.0f, 90.0f});
    core.AddComponent(entity2, Components::Position{84.0f, 42.0f});
    core.AddComponent(entity2, Components::Velocity{0.5f, 0.5f});

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "entity1 signature:" << core.getSignature(entity1) << std::endl;
    std::cout << "entity2 signature:" << core.getSignature(entity2) << std::endl;

    std::cout << "-----------------------------------\n";

    std::cout << "Signature system: " << velocitySystemSignature << std::endl;

    std::cout << "-----------------------------------\n";
    std::cout << "Initial Entity 1 Position: ";
    std::cout << core.GetComponent<Components::Position>(entity1) << std::endl;
    std::cout << "-----------------------------------\n";
    std::cout << "Initial Entity 2 Position: ";
    std::cout << core.GetComponent<Components::Position>(entity2) << std::endl;
    std::cout << "Initial Entity 2 Velocity: ";
    std::cout << core.GetComponent<Components::Velocity>(entity2) << std::endl;

    std::cout << "-----------------------------------\n";

    std::vector<std::size_t> entities = core.getEntitiesWithSignature(velocitySystemSignature);
    velocitySystem->update(core.GetComponents<Components::Position>(),
                           core.GetComponents<Components::Velocity>(),
                           entities);

    std::cout << "Updated Entity 1 Position: ";
    std::cout << core.GetComponent<Components::Position>(entity1) << std::endl;
    std::cout << "Updated Entity 2 Position: ";
    std::cout << core.GetComponent<Components::Position>(entity2) << std::endl;

    return 0;
}
