/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Score
*/

#include "Score.hh"

Rtype::Command::Player::Score::Score(std::map<int, Rtype::client_info> players, int score):
    _endpoint(), _players(players), _score(score)
{
}

Rtype::Command::Player::Score::Score(udp::endpoint endpoint):
    _endpoint(endpoint), _players(), _score(-1)
{
}

Rtype::Command::Player::Score::~Score()
{
}

void Rtype::Command::Player::Score::execute_client_side()
{
}

void Rtype::Command::Player::Score::execute_server_side()
{
}
