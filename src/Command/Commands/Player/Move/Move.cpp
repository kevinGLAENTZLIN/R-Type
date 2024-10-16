/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Move
*/

#include "Move.hh"

void Rtype::Command::Player::Move::set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int playerID, int x, int y)
{
    _players = players;
    _playerID = playerID;
    _x = x;
    _y = y;
}

void Rtype::Command::Player::Move::set_client(udp::endpoint endpoint, int x, int y)
{
    _endpoint = endpoint;
    _x = x;
    _y = y;
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
