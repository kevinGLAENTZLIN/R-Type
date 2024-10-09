/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Fired
*/

#pragma once
#include "../../../ICommand.hh"
#include "../../../../Server/udp_server.hh"

namespace Rtype
{
    namespace Command
    {
        namespace Projectile
        {
            class Fired: ICommand{
                public:
                    Fired(std::map<int, Rtype::client_info> players, int projectileType, int projectileID, int xOrigin, int yOrigin, int xVector, int yVector);
                    Fired(udp::endpoint endpoint, int projectileType, int projectileID, int xVector, int yVector);
                    ~Fired();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::map<int, Rtype::client_info> _players;
                    int _projectileType;
                    int _projectileID;
                    int _xOrigin;
                    int _yOrigin;
                    int _xVector;
                    int _yVector;
            };
        }
    }
}
