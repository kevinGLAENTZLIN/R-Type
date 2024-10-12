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

void Rtype::Command::GameInfo::Join_game::set_server(udp::endpoint endpoint, Rtype::Game_info &game)
{
    _endpoint = endpoint;
    _game = game;
}

Rtype::Command::GameInfo::Join_game::~Join_game()
{
}

void Rtype::Command::GameInfo::Join_game::execute_client_side()
{
}

void Rtype::Command::GameInfo::Join_game::execute_server_side()
{
}
