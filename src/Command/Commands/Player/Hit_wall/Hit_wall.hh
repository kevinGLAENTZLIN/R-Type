/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hit_wall
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
            class Hit_wall: ICommand{
                public:
                    Hit_wall(std::map<int, Rtype::client_info> players, int playerID);
                    Hit_wall(udp::endpoint endpoint);
                    ~Hit_wall();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::map<int, Rtype::client_info> _players;
                    int _playerID;
            };
        }
    }
}
