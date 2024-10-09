/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
*/

#include "Die.hh"

Rtype::Command::Enemy::Die::Die(std::map<int, Rtype::client_info> players, int mobID):
    _players(players), _mobID(mobID)
{
}

Rtype::Command::Enemy::Die::Die():
    _players(), _mobID(-1)
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
