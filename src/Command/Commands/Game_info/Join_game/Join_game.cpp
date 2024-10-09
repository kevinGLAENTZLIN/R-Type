/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Join_game
*/

#include "Join_game.hh"

Rtype::Command::GameInfo::Join_game::Join_game(udp::endpoint endpoint, int gameRoom):
    _endpoint(endpoint), _gameRoom(gameRoom), _game()
{
}

Rtype::Command::GameInfo::Join_game::Join_game(udp::endpoint endpoint, Rtype::Game_info &game):
    _endpoint(endpoint), _gameRoom(-1), _game(game)
{
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
