/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EnemySpawnData.cpp
*/

#include "EnemySpawnData.hh"

Rtype::EnemySpawnData::EnemySpawnData()
{}

void Rtype::EnemySpawnData::setType(enemiesTypeEnum_t type)
{
    _type = type;
}

void Rtype::EnemySpawnData::setPositionX(float x)
{
    _position_x = x;
}

void Rtype::EnemySpawnData::setPositionY(float y)
{
    _position_y = y;
}

void Rtype::EnemySpawnData::setModel(std::string model)
{
    _model = model;
}

void Rtype::EnemySpawnData::setSpawnTime(std::pair <int, int> spawnTime)
{
    _spawnTime = spawnTime;
}

enemiesTypeEnum_t Rtype::EnemySpawnData::getType() const
{
    return _type;
}

float Rtype::EnemySpawnData::getPositionX() const
{
    return _position_x;
}

float Rtype::EnemySpawnData::getPositionY() const
{
    return _position_y;
}

std::string Rtype::EnemySpawnData::getModel() const
{
    return _model;
}

std::pair <int, int> Rtype::EnemySpawnData::getSpawnTime() const
{
    return _spawnTime;
}
