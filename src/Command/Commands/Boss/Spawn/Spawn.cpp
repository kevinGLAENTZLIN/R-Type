/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#include "Spawn.hh"

void Rtype::Command::Boss::Spawn::set_server(std::map<int, Rtype::client_info> players, int bossType, int x, int y)
{
    _players = players;
    _bossType = bossType;
    _x = x;
    _y = y;
}

void Rtype::Command::Boss::Spawn::set_client()
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