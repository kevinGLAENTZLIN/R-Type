/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
*/

#include "Die.hh"

Rtype::Command::Boss::Die::Die(std::map<int, Rtype::client_info> players, int bossType):
    _players(players), _bossType(bossType)
{
}

Rtype::Command::Boss::Die::Die():
    _players(), _bossType(-1)
{
}

Rtype::Command::Boss::Die::~Die()
{
}

void Rtype::Command::Boss::Die::execute_client_side()
{
}

void Rtype::Command::Boss::Die::execute_server_side()
{
}
