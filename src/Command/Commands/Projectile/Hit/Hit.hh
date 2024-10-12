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
            class Hit: public ICommand{
                public:
                    Hit();
                    ~Hit();

                    void set_server(std::map<int, Rtype::client_info> players, int projectileID);
                    void set_client();

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
