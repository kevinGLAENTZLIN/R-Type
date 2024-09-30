/*
** EPITECH PROJECT, 2024
** EntityManager.hh
** File description:
** EntityManager class
*/
#include "EntityManager.hh"

ECS::EntityManager::EntityManager::EntityManager():
    _mLivingEntityCount(0)
{
    for (std::size_t entity = 0; entity < MAX_ENTITIES; ++entity) {
        _mAvailableEntities.push(entity);
    }
}

std::size_t ECS::EntityManager::EntityManager::createEntity()
{
    if (_mLivingEntityCount > MAX_ENTITIES)
        return MAX_ENTITIES;
    std::size_t id = _mAvailableEntities.front();
    _mAvailableEntities.pop();
    ++_mLivingEntityCount;
    return id;
}

void ECS::EntityManager::EntityManager::destroyEntity(std::size_t entity)
{
    _mSignatures[entity].reset();
    _mAvailableEntities.push(entity);
    --_mLivingEntityCount;
}

void ECS::EntityManager::EntityManager::setSignature(std::size_t entity, Signature signature)
{
    if (entity >= MAX_ENTITIES) {
        return;
    }
    _mSignatures[entity] = signature;
}

Signature ECS::EntityManager::EntityManager::getSignature(std::size_t entity) const
{
    if (entity >= MAX_ENTITIES) {
        return Signature();
    }
    return _mSignatures[entity];
}

std::vector<std::size_t> ECS::EntityManager::EntityManager::getEntities() const
{
    std::vector<std::size_t> activeEntities;

    for (std::size_t entity = 0; entity < MAX_ENTITIES; ++entity) {
        if (_mSignatures[entity].any()) {
            activeEntities.push_back(entity);
        }
    }
    return activeEntities;
}
