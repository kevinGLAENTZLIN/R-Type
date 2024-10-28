/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Power_up
*/

#include "Power_up.hh"

void Rtype::Command::Player::Power_up::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int playerID, int powerUpID)
{
    _players = players;
    _playerID = playerID;
    _powerUpID = powerUpID;
}

void Rtype::Command::Player::Power_up::set_client(udp::endpoint endpoint, int powerUpID)
{
    _endpoint = endpoint;
    _powerUpID = powerUpID;
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
