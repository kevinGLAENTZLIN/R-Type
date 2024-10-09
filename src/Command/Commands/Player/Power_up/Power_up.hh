/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Power_up
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
            class Power_up: ICommand{
                public:
                    Power_up(std::map<int, Rtype::client_info> players, int playerID, int powerUpID);
                    Power_up(udp::endpoint endpoint, int powerUpID);
                    ~Power_up();

                    void execute_client_side();
                    void execute_server_side();
            
                protected:
                private:
                    udp::endpoint _endpoint;
                    std::map<int, Rtype::client_info> _players;
                    int _playerID;
                    int _powerUpID;
            };
        }
    }
}
