/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Attack
*/

#pragma once
#include "../../../ICommand.hh"
#include "../../../../Server/udp_server.hh"

namespace Rtype
{
    namespace Command
    {
        namespace Player
        {
            class Attack: public ICommand{
                public:
                    Attack() = default;
                    ~Attack();

                    void set_server(std::map<int, Rtype::client_info> players, int projectileID);
                    void set_client(udp::endpoint endpoint, int projectileID);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::map<int, Rtype::client_info> _players;
                    int _projectileID;
            };
        }
    }
}
