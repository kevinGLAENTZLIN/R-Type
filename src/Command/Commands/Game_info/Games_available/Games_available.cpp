/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Games_available
*/

#include "Games_available.hh"

void Rtype::Command::GameInfo::Games_available::set_client(udp::endpoint endpoint)
{
    _endpoint = endpoint;
}

void Rtype::Command::GameInfo::Games_available::set_server(udp::endpoint endpoint, std::vector<std::shared_ptr<Rtype::Game_info>> games)
{
    _endpoint = endpoint;
    _games = games;
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
