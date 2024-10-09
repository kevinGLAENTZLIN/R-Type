/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Attack
*/

#include "Attack.hh"

Rtype::Command::Enemy::Attack::Attack(std::map<int, Rtype::client_info> players, int bossType, int bossAttackType):
    _players(players), _bossType(bossType), _bossAttackType(bossAttackType)
{
}

Rtype::Command::Enemy::Attack::Attack():
    _players(), _bossType(-1), _bossAttackType(-1)
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
