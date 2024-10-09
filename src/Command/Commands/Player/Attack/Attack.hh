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
            class Attack: ICommand{
                public:
                    Attack(std::map<int, Rtype::client_info> players, int projectileID);
                    Attack(udp::endpoint endpoint, int projectileID);
                    ~Attack();

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
