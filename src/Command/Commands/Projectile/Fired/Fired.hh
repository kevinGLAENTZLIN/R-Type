/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Fired
*/

#pragma once
#include "../../../ICommand.hh"
#include "../../../../Server/Client_info.hh"

namespace Rtype
{
    namespace Command
    {
        namespace Projectile
        {
            class Fired: public ICommand{
                public:
                    Fired() = default;
                    ~Fired();

                    void set_server(std::map<int, Rtype::client_info> players, int projectileType, int projectileID, int xOrigin, int yOrigin, int xVector, int yVector);
                    void set_client(udp::endpoint endpoint, int projectileType, int projectileID, int xVector, int yVector);

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
