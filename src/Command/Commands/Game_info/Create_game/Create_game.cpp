/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Create_game
*/

#include "Create_game.hh"

Rtype::Command::GameInfo::Create_game::Create_game(udp::endpoint endpoint):
    _endpoint(endpoint)
{
}

Rtype::Command::GameInfo::Create_game::Create_game(udp::endpoint endpoint, std::vector<int> &games):
    _endpoint(endpoint), _games(games)
{
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
