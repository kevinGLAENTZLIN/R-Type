/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Attack
*/

#include "Attack.hh"

Rtype::Command::Enemy::Attack::Attack(std::map<int, Rtype::client_info> players, int mobID):
    _players(players), _mobID(mobID)
{
}

Rtype::Command::Enemy::Attack::Attack():
    _players(), _mobID(-1)
{
}

Rtype::Command::Enemy::Attack::~Attack()
{
}

void Rtype::Command::Enemy::Attack::execute_client_side()
{
}

void Rtype::Command::Enemy::Attack::execute_server_side()
{
}
