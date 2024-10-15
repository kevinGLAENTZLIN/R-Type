/*
** EPITECH PROJECT, 2024
** R-Type - Components : AI
** File description:
** AI Component
*/
#include "AI.hh"

ECS::Components::AI::AI(ECS::enemiesTypeEnum_t enemyType):
    _enemyType(enemyType)
{}

ECS::enemiesTypeEnum_t ECS::Components::AI::getEnemyType() const
{
    return _enemyType;
}

void ECS::Components::AI::setEnemyType(ECS::enemiesTypeEnum_t enemyType)
{
    _enemyType = enemyType;
}
