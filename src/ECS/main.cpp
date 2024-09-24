/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** main to test
*/

#include "Component/ComponentManager/SparseArray.hpp"
#include "Component/Position/Position.hpp"
#include "Component/Velocity/Velocity.hh"
#include "Entity/EntityManager/EntityManager.hh"
#include "System/SystemVelocity/SystemVelocity.hpp"
#include "System/SystemManager/SystemManager.hpp"
#include "Component/ComponentManager/ComponentManager.hpp"

int main(void)
{
    EntityManager em;
    SystemManager systemManager;
    ComponentManager::ComponentManager componentManager;

    componentManager.registerComponent<Components::Position>();
    componentManager.registerComponent<Components::Velocity>();
    auto velocitySystem = systemManager.RegisterSystem<SystemVelocity>();

    Signature velocitySystemSignature;
    velocitySystemSignature.set(1);
    velocitySystemSignature.set(2);
    systemManager.SetSignature<SystemVelocity>(velocitySystemSignature);
    std::cout << "-----------------------------------\n";

    std::string systemTypeName = typeid(SystemVelocity).name();
    std::cout << "Velocity System Type Name: " << systemTypeName << std::endl;

    std::size_t entity1 = em.CreateEntity();
    std::size_t entity2 = em.CreateEntity();

    std::cout << "Entity 1: " << entity1 << std::endl;
    std::cout << "Entity 2: " << entity2 << std::endl;

    Signature entity1Signature;
    entity1Signature.set(1);
    em.SetSignature(entity1, entity1Signature);

    Signature entity2Signature;
    entity2Signature.set(1);
    entity2Signature.set(2);
    em.SetSignature(entity2, entity2Signature);

    std::cout << "-----------------------------------\n";

    std::cout << "Entity 1 Signature: " << em.GetSignature(entity1) << std::endl;
    std::cout << "Entity 2 Signature: " << em.GetSignature(entity2) << std::endl;

    std::cout << "-----------------------------------\n";

    ComponentManager::SparseArray<Components::Position> positionArray = componentManager.getComponents<Components::Position>();
    ComponentManager::SparseArray<Components::Velocity> velocityArray = componentManager.getComponents<Components::Velocity>();

    positionArray.insertAt(entity1, Components::Position{1.0f, 2.0f});
    positionArray.insertAt(entity2, Components::Position{4.4f, 5.7f});
    velocityArray.insertAt(entity2, Components::Velocity{0.5f, 0.5f});

    systemManager.EntitySignatureChanged(entity1, entity1Signature);
    systemManager.EntitySignatureChanged(entity2, entity2Signature);
    std::cout << "Initial Entity 1 Position: " << positionArray[entity1].value() << std::endl;
    std::cout << "Initial Entity 2 Position: " << positionArray[entity2].value() << std::endl;

    std::cout << "-----------------------------------\n";

    std::vector<std::size_t> entiti;
    entiti = {entity1, entity2};
    velocitySystem->update(positionArray, velocityArray, entiti);

    std::cout << "Updated Entity 1 Position: " << positionArray[entity1].value() << std::endl;
    std::cout << "Updated Entity 2 Position: " << positionArray[entity2].value() << std::endl;
    return 0;
}
