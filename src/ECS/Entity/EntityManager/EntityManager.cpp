/*
** EPITECH PROJECT, 2024
** EntityManeger.hh
** File description:
** EntityManeger class
*/

#include "EntityManager.hh"

EntityManager::EntityManager():
    mLivingEntityCount(0)
{
    for (std::size_t entity = 0; entity < MAX_ENTITIES; ++entity) {
        mAvailableEntities.push(entity);
    }
}

std::size_t EntityManager::CreateEntity()
{
    if (mLivingEntityCount > MAX_ENTITIES)
        return MAX_ENTITIES;
    std::size_t id = mAvailableEntities.front();
    mAvailableEntities.pop();
    ++mLivingEntityCount;
    return id;
}

void EntityManager::DestroyEntity(std::size_t entity)
{
    mSignatures[entity].reset();
    mAvailableEntities.push(entity);
    --mLivingEntityCount;
}

void EntityManager::SetSignature(std::size_t entity, Signature signature)
{
    if (entity >= MAX_ENTITIES) {
        return;
    }
    mSignatures[entity] = signature;
}

Signature EntityManager::GetSignature(std::size_t entity) const
{
    if (entity >= MAX_ENTITIES) {
        return Signature();
    }
    return mSignatures[entity];
}
