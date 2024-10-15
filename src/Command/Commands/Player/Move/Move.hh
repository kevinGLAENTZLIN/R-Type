/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Move
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace Player
        {
            class Move: public ACommand{
                public:
                    Move() = default;
                    ~Move();

                    void set_server(std::map<int, Rtype::client_info> players, int playerID, int x, int y);
                    void set_client(udp::endpoint endpoint, int x, int y);

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
