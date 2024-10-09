/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#include "Spawn.hh"

Rtype::Command::Enemy::Spawn::Spawn(std::map<int, Rtype::client_info> players, int mobType, int mobID, int x, int y):
    _players(players), _mobType(mobType), _mobID(mobID), _x(x), _y(y)
{
}

Rtype::Command::Enemy::Spawn::Spawn():
    _players(), _mobType(-1), _mobID(-1), _x(-1), _y(-1)
{
}

Rtype::Command::Enemy::Spawn::~Spawn()
{
}

void Rtype::Command::Enemy::Spawn::execute_client_side()
{
}

void Rtype::Command::Enemy::Spawn::execute_server_side()
{
}
