/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
*/

#include "Die.hh"

void Rtype::Command::Enemy::Die::set_server(std::map<int, Rtype::client_info> players, int mobID)
{
    _players = players;
    _mobID = mobID;
}

void Rtype::Command::Enemy::Die::set_client()
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
