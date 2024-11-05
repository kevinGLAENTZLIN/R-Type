/*
** EPITECH PROJECT, 2024
** EntityManager.hh
** File description:
** EntityManager class
*/
#include "EntityManager.hh"
#include <mutex>

ECS::EntityManager::EntityManager::EntityManager():
    _mLivingEntityCount(0)
{}

std::size_t ECS::EntityManager::EntityManager::createEntity()
{
    std::cout << "====== createEntity _mLivingEntityCount" << _mLivingEntityCount << std::endl;
    std::lock_guard<std::mutex> lock(_mMutex);
    std::size_t id;

    id = _mLivingEntityCount;
    ++_mLivingEntityCount;
    return id;
}

void ECS::EntityManager::EntityManager::destroyEntity(std::size_t entity)
{
    std::lock_guard<std::mutex> lock(_mMutex);
    _mSignatures[entity].reset();
}

void ECS::EntityManager::EntityManager::setSignature(std::size_t entity, Signature signature)
{
    _mSignatures[entity] = signature;
}

Signature ECS::EntityManager::EntityManager::getSignature(std::size_t entity) const
{
    return _mSignatures[entity];
}

std::vector<std::size_t> ECS::EntityManager::EntityManager::getEntities() const
{
    std::vector<std::size_t> activeEntities;

    for (std::size_t entity = 0; entity < _mLivingEntityCount; ++entity) {
        if (_mSignatures[entity].any()) {
            activeEntities.push_back(entity);
        }
    }
    return activeEntities;
}
