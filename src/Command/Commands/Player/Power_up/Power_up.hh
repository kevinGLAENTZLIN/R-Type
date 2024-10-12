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
            class Power_up: public ICommand{
                public:
                    Power_up() = default;
                    ~Power_up();

                    void set_server(std::map<int, Rtype::client_info> players, int playerID, int powerUpID);
                    void set_client(udp::endpoint endpoint, int powerUpID);

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
