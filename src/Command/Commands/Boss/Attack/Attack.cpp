/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Attack
*/

#include "Attack.hh"

Rtype::Command::Boss::Attack::Attack(std::map<int, Rtype::client_info> players, int bossType, int bossAttackType):
    _players(players), _bossType(bossType), _bossAttackType(bossAttackType)
{
}

Rtype::Command::Boss::Attack::Attack():
    _players(), _bossType(-1), _bossAttackType(-1)
{
}

Rtype::Command::Boss::Attack::~Attack()
{
}

void Rtype::Command::Boss::Attack::execute_client_side()
{
}

void Rtype::Command::Boss::Attack::execute_server_side()
{
}
