/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game_result
*/

#include "Game_result.hh"

void Rtype::Command::GameInfo::Game_result::set_client()
{
}

void Rtype::Command::GameInfo::Game_result::set_server(udp::endpoint endpoint, Rtype::Game_info game)
{
    _endpoint = endpoint;
    _game = game;
}

Rtype::Command::GameInfo::Game_result::~Game_result()
{
}

void Rtype::Command::GameInfo::Game_result::execute_client_side()
{
    std::cerr << "This command have no client side" << std::endl;
}

void Rtype::Command::GameInfo::Game_result::execute_server_side()
{
}
