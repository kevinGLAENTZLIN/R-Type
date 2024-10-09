/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hit_wall
*/

#include "Hit_wall.hh"

Rtype::Command::Player::Hit_wall::Hit_wall(std::map<int, Rtype::client_info> players, int playerID):
    _endpoint(), _players(players), _playerID(playerID)
{
}

Rtype::Command::Player::Hit_wall::Hit_wall(udp::endpoint endpoint):
    _endpoint(endpoint), _players(), _playerID(playerID)
{
}

Rtype::Command::Player::Hit_wall::~Hit_wall()
{
}

void Rtype::Command::Player::Hit_wall::execute_client_side()
{
}

void Rtype::Command::Player::Hit_wall::execute_server_side()
{
}
