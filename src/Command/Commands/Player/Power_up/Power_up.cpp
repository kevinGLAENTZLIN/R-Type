/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Power_up
*/

#include "Power_up.hh"

Rtype::Command::Player::Power_up::Power_up(std::map<int, Rtype::client_info> players, int playerID, int powerUpID):
    _endpoint(), _players(players), _playerID(playerID), _powerUpID(powerUpID)
{
}

Rtype::Command::Player::Power_up::Power_up(udp::endpoint endpoint, int powerUpID):
    _endpoint(endpoint), _players(), _playerID(-1), _powerUpID(powerUpID)
{
}

Rtype::Command::Player::Power_up::~Power_up()
{
}

void Rtype::Command::Player::Power_up::execute_client_side()
{
}

void Rtype::Command::Player::Power_up::execute_server_side()
{
}
