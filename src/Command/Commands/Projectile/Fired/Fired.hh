/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Fired
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace Projectile
        {
            class Fired: public ACommand{
                public:
                    Fired() = default;
                    ~Fired();

                    void set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int projectileType, int projectileID, double xOrigin, double yOrigin, double xVector, double yVector);
                    void set_client(udp::endpoint endpoint, int projectileType, int projectileID, double xVector, double yVector);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::map<int, std::shared_ptr<Rtype::client_info>> _players;
                    int _projectileType;
                    int _projectileID;
                    double _xOrigin;
                    double _yOrigin;
                    double _xVector;
                    double _yVector;
            };
        }
    }
}
