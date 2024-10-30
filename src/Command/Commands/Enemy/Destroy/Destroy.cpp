/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Destroy
*/

#include "Destroy.hh"

void Rtype::Command::Enemy::Destroy::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int mobID)
{
    _players = players;
    _mobID = mobID;
}

void Rtype::Command::Enemy::Destroy::set_client()
{
}

Rtype::Command::Enemy::Destroy::~Destroy()
{
}

void Rtype::Command::Enemy::Destroy::execute_client_side()
{
}

void Rtype::Command::Enemy::Destroy::execute_server_side()
{
}
