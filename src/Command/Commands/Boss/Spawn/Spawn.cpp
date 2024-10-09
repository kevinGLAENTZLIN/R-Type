/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#include "Spawn.hh"

Rtype::Command::Boss::Spawn::Spawn(std::map<int, Rtype::client_info> players, int bossType, int x, int y):
    _players(players), _bossType(bossType), _x(x), _y(y)
{
}

Rtype::Command::Boss::Spawn::Spawn():
    _players(), _bossType(-1), _x(-1), _y(-1)
{
}

Rtype::Command::Boss::Spawn::~Spawn()
{
}

void Rtype::Command::Boss::Spawn::execute_client_side()
{
}

void Rtype::Command::Boss::Spawn::execute_server_side()
{
}
