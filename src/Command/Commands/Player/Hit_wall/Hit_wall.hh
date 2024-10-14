/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hit_wall
*/

#pragma once
#include "../../../ICommand.hh"
#include "../../../../Server/Client_info.hh"

namespace Rtype
{
    namespace Command
    {
        namespace Player
        {
            class Hit_wall: public ICommand{
                public:
                    Hit_wall() = default;
                    ~Hit_wall();

                    void set_server(std::map<int, Rtype::client_info> players, int playerID);
                    void set_client(udp::endpoint endpoint);

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
