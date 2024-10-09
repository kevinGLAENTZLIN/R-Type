/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#include "Spawn.hh"

Rtype::Command::Player::Spawn::Spawn(std::map<int, Rtype::client_info> players, int playerID, int x, int y):
    _players(players), _playerID(playerID), _x(x), _y(y)
{
}

Rtype::Command::Player::Spawn::Spawn():
    _players(), _playerID(-1), _x(-1), _y(-1)
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
