/*
** EPITECH PROJECT, 2024
** R-Type - Core : Core
** File description:
** Core class is the main class of the ECS.
** It will coordinate the behaviors of the managers.
*/
#include "Core.hpp"

ECS::Core::Core::Core()
{
    _entityManager = std::make_shared<EntityManager::EntityManager>();
    _systemManager = std::make_shared<SystemManager::SystemManager>();
    _componentManager = std::make_shared<ComponentManager::ComponentManager>();
}

std::size_t ECS::Core::Core::createEntity()
{
    return _entityManager->createEntity();
}

void ECS::Core::Core::destroyEntity(std::size_t entity)
{
    _entityManager->destroyEntity(entity);
    _systemManager->entityDestroyed(entity);
}

Signature ECS::Core::Core::getSignature(std::size_t entity) const
{
    return _entityManager->getSignature(entity);
}
