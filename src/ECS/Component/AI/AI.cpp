/*
** EPITECH PROJECT, 2024
** R-Type - Components : AI
** File description:
** AI Component
*/
#include "AI.hh"

ECS::Components::AI::AI(enemiesTypeEnum_t enemyType):
    _enemyType(enemyType)
{}

enemiesTypeEnum_t ECS::Components::AI::getEnemyType() const
{
    return _enemyType;
}

void ECS::Components::AI::setEnemyType(enemiesTypeEnum_t enemyType)
{
    _enemyType = enemyType;
}
