/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
*/

#include "Die.hh"

Rtype::Command::Enemy::Die::Die(std::map<int, Rtype::client_info> players, int bossType):
    _players(players), _bossType(bossType)
{
}

Rtype::Command::Enemy::Die::Die():
    _players(), _bossType(-1)
{
}

Rtype::Command::Enemy::Die::~Die()
{
}

void Rtype::Command::Enemy::Die::execute_client_side()
{
}

void Rtype::Command::Enemy::Die::execute_server_side()
{
}
