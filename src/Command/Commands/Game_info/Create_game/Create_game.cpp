/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Create_game
*/

#include "Create_game.hh"

void Rtype::Command::GameInfo::Create_game::set_client(udp::endpoint endpoint)
{
    _endpoint = endpoint;
}

void Rtype::Command::GameInfo::Create_game::set_server(udp::endpoint endpoint, std::vector<Rtype::Game_info> &games)
{
    _endpoint = endpoint;
    _games = games;
}

Rtype::Command::GameInfo::Create_game::~Create_game()
{
}

void Rtype::Command::GameInfo::Create_game::execute_client_side()
{
	// Do Something who will be executed by the Client
}

void Rtype::Command::GameInfo::Create_game::execute_server_side()
{
	// Do Something who will be executed by the Server
}
