/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Join_game
*/

#include "Join_game.hh"

void Rtype::Command::GameInfo::Join_game::set_client(udp::endpoint endpoint, int gameRoom)
{
    _endpoint = endpoint;
    _gameRoom = gameRoom;
}

void Rtype::Command::GameInfo::Join_game::set_server(udp::endpoint endpoint, std::shared_ptr<Rtype::Game_info> game, std::shared_ptr<Rtype::client_info> client_info)
{
    _endpoint = endpoint;
    _gameInfo = game;
    _clientInfo = client_info;
}

Rtype::Command::GameInfo::Join_game::~Join_game()
{
}

void Rtype::Command::GameInfo::Join_game::execute_client_side()
{
}

void Rtype::Command::GameInfo::Join_game::execute_server_side()
{
    _gameInfo->connectPlayer(_clientInfo);
}
