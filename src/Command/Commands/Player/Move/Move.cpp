/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Move
*/

#include "Move.hh"

void Rtype::Command::Player::Move::set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int playerID, int x, int y)
{
    _players = players;
    _playerID = playerID;
    _x = x;
    _y = y;
}

void Rtype::Command::Player::Move::set_client(udp::endpoint endpoint, int x, int y)
{
    _endpoint = endpoint;
    _x = x;
    _y = y;
}

Rtype::Command::Player::Move::~Move()
{
}

void Rtype::Command::Player::Move::execute_client_side()
{
    sendToEndpoint(Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerMove, _x, _y);
}

void Rtype::Command::Player::Move::execute_server_side()
{
    _players[_playerID]->setX(_x);
    _players[_playerID]->setX(_y);
    for (auto player: _players) {
        _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
        sendToEndpoint(Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerMove, _playerID, _x, _y);
    }
    _game->movePlayer(_playerID, _x * 1., _y * 1.);
}
