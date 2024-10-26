/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Fired
*/

#include "Fired.hh"

void Rtype::Command::Projectile::Fired::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int projectileType, int projectileID, double xOrigin, double yOrigin, double xVector, double yVector)
{
    _players = players;
    _projectileType = projectileType;
    _projectileID = projectileID;
    _xOrigin = xOrigin;
    _yOrigin = yOrigin;
    _xVector = xVector;
    _yVector = yVector;
}

void Rtype::Command::Projectile::Fired::set_client(udp::endpoint endpoint, int projectileType, int projectileID, double xVector, double yVector)
{
    _endpoint = endpoint;
    _projectileType = projectileType;
    _projectileID = projectileID;
    _xVector = xVector;
    _yVector = yVector;
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
