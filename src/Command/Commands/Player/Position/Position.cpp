/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position.cpp
*/

#include "Position.hh"

Rtype::Command::Player::Position::~Position()
{
}

void Rtype::Command::Player::Position::set_client()
{
}

void Rtype::Command::Player::Position::set_server(double x, double y)
{
    _x = x;
    _y = y;
}

void Rtype::Command::Player::Position::execute_client_side()
{
}

void Rtype::Command::Player::Position::execute_server_side()
{
    sendToEndpoint(Utils::InfoTypeEnum::Player, Utils::PlayerEnum::Position, _x, _y);
}
