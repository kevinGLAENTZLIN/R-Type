/*
** EPITECH PROJECT, 2024
** R-Type - Core : Core
** File description:
** Core class is the main class of the ECS.
** It will coordinate the behaviors of the managers.
*/

#include "Core.hpp"

ECS::Core::Core()
{
    _entityManager = std::make_shared<EntityManager>();
    _systemManager = std::make_shared<SystemManager>();
    _componentManager = std::make_shared<ComponentManager::ComponentManager>();
}

std::size_t ECS::Core::createEntity()
{
    return _entityManager->CreateEntity();
}

void ECS::Core::destroyEntity(std::size_t entity)
{
    _entityManager->DestroyEntity(entity);
    _systemManager->EntityDestroyed(entity);
}

Signature ECS::Core::getSignature(std::size_t entity) const
{
    return _entityManager->GetSignature(entity);
}
