/*
** EPITECH PROJECT, 2024
** R-Type - Components : AI
** File description:
** AI Component
*/
#include "AI.hh"

ECS::Components::AI::AI(enemiesTypeEnum_t enemyType):
    _enemyType(enemyType), _isFiring(false), _cooldown(0)
{}

enemiesTypeEnum_t ECS::Components::AI::getEnemyType() const
{
    return _enemyType;
}

void ECS::Components::AI::setEnemyType(enemiesTypeEnum_t enemyType)
{
    _enemyType = enemyType;
}

void ECS::Components::AI::setFiring(bool isFiring)
{
    _isFiring = isFiring;
}

void ECS::Components::AI::flipFiring()
{
    _isFiring = !_isFiring;
}

bool ECS::Components::AI::isFiring() const
{
    return _isFiring;
}

void ECS::Components::AI::setCooldown(std::size_t cooldown)
{
    _cooldown = cooldown;
}

std::size_t ECS::Components::AI::getCooldown() const
{
    return _cooldown;
}
