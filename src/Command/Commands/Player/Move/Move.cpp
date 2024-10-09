/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Move
*/

#include "Move.hh"

Rtype::Command::Player::Move::Move(std::map<int, Rtype::client_info> players, int playerID, int x, int y):
    _endpoint(), _players(players), _playerID(playerID), _x(x), _y(y) 
{
}

Rtype::Command::Player::Move::Move(udp::endpoint endpoint, int x, int y):
    _endpoint(endpoint), _players(), _playerID(-1), _x(x), _y(y) 
{
}

Rtype::Command::Player::Move::~Move()
{
}

void Rtype::Command::Player::Move::execute_client_side()
{
}

void Rtype::Command::Player::Move::execute_server_side()
{
}
