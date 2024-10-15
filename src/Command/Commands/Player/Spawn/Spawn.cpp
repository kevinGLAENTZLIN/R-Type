/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#include "Spawn.hh"

void Rtype::Command::Player::Spawn::set_server(std::map<int, Rtype::client_info> players, int playerID, int x, int y)
{
    _players = players;
    _playerID = playerID;
    _x = x;
    _y = y;
}

void Rtype::Command::Player::Spawn::set_client()
{
}

Rtype::Command::Player::Spawn::~Spawn()
{
}

void Rtype::Command::Player::Spawn::execute_client_side()
{
}

void Rtype::Command::Player::Spawn::execute_server_side()
{
}
