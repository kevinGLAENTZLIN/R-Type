/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Attack
*/

#include "Attack.hh"

Rtype::Command::Player::Attack::Attack(std::map<int, Rtype::client_info> players, int projectileID):
    _endpoint(), _players(players), _projectileID(projectileID)
{
}

Rtype::Command::Player::Attack::Attack(udp::endpoint endpoint, int projectileID):
    _endpoint(endpoint), _players(), _projectileID(projectileID)
{
}

Rtype::Command::Player::Attack::~Attack()
{
}

void Rtype::Command::Player::Attack::execute_client_side()
{
}

void Rtype::Command::Player::Attack::execute_server_side()
{
}
