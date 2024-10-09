/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hit
*/

#include "Hit.hh"

Rtype::Command::Projectile::Hit::Hit(std::map<int, Rtype::client_info> players, int projectileID):
    _players(players), _projectileID(projectileID)
{
}

Rtype::Command::Projectile::Hit::Hit():
    _players(), _projectileID(-1)
{
}

Rtype::Command::Projectile::Hit::~Hit()
{
}

void Rtype::Command::Projectile::Hit::execute_client_side()
{
}

void Rtype::Command::Projectile::Hit::execute_server_side()
{
}
