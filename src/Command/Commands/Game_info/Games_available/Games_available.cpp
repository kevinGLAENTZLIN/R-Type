/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Games_available
*/

#include "Games_available.hh"

Rtype::Command::GameInfo::Games_available::Games_available(udp::endpoint endpoint):
    _endpoint(endpoint), _games()
{
}

Rtype::Command::GameInfo::Games_available::Games_available(udp::endpoint endpoint, std::vector<Rtype::Game_info> games):
    _endpoint(endpoint), _games(games)
{
}

Rtype::Command::GameInfo::Games_available::~Games_available()
{
}

void Rtype::Command::GameInfo::Games_available::execute_client_side()
{
}

void Rtype::Command::GameInfo::Games_available::execute_server_side()
{
}
