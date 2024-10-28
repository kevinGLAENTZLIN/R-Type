/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#include "Spawn.hh"

void Rtype::Command::Enemy::Spawn::set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int mobType, int mobID, double x, double y)
{
    _players = players;
    _mobType = mobType;
    _mobID = mobID;
    _x = x;
    _y = y;
}

void Rtype::Command::Enemy::Spawn::set_client()
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
