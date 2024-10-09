/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
*/

#include "Die.hh"

Rtype::Command::Player::Die::Die(std::map<int, Rtype::client_info> players, int playerID):
    _players(players), _playerID(playerID)
{
}

Rtype::Command::Player::Die::Die():
    _players(), _playerID(-1)
{
}

Rtype::Command::Player::Die::~Die()
{
}

void Rtype::Command::Player::Die::execute_client_side()
{
}

void Rtype::Command::Player::Die::execute_server_side()
{
}
