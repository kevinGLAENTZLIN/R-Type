/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Move
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
            class Move: ICommand{
                public:
                    Move(std::map<int, Rtype::client_info> players, int playerID, int x, int y);
                    Move(udp::endpoint endpoint, int x, int y);
                    ~Move();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::map<int, Rtype::client_info> _players;
                    int _playerID;
                    int _x;
                    int _y;
            };
        }
    }
}
