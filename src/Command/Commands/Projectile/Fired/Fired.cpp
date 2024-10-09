/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Fired
*/

#include "Fired.hh"

Rtype::Command::Projectile::Fired::Fired(std::map<int, Rtype::client_info> players, int projectileType, int projectileID, int xOrigin, int yOrigin, int xVector, int yVector):
    _endpoint(), _players(players), _projectileType(projectileType), _projectileID(projectileID),
    _xOrigin(xOrigin), _yOrigin(yOrigin), _xVector(xVector), _yVector(yVector)
{
}

Rtype::Command::Projectile::Fired::Fired(udp::endpoint endpoint, int projectileType, int projectileID, int xVector, int yVector):
    _endpoint(endpoint), _players(), _projectileType(projectileType), _projectileID(projectileID),
    _xVector(xVector), _yVector(yVector)
{
}

Rtype::Command::Projectile::Fired::~Fired()
{
}

void Rtype::Command::Projectile::Fired::execute_client_side()
{
}

void Rtype::Command::Projectile::Fired::execute_server_side()
{
}
