/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hit
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
            class Hit: ICommand{
                public:
                    Hit(std::map<int, Rtype::client_info> players, int projectileID);
                    Hit();
                    ~Hit();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    std::map<int, Rtype::client_info> _players;
                    int _projectileID;
            };
        }
    }
}
