/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
*/

#include "Die.hh"

void Rtype::Command::Player::Die::set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int playerID)
{
    _players = players;
    _playerID = playerID;
}

void Rtype::Command::Player::Die::set_client()
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
