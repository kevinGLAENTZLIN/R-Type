/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Level_complete
*/

#include "Level_complete.hh"

Rtype::Command::GameInfo::Level_complete::Level_complete():
    _endpoint(), _game()
{
}

Rtype::Command::GameInfo::Level_complete::Level_complete(udp::endpoint endpoint, Rtype::Game_info &game):
    _endpoint(endpoint), _game(game)
{
}

Rtype::Command::GameInfo::Level_complete::~Level_complete()
{
}

void Rtype::Command::GameInfo::Level_complete::execute_client_side()
{
}

void Rtype::Command::GameInfo::Level_complete::execute_server_side()
{
}
