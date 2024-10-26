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

                    void set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int playerID, double x, double y);
                    void set_client(udp::endpoint endpoint, double x, double y);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::map<int, std::shared_ptr<Rtype::client_info>> _players;
                    int _playerID;
                    double _x;
                    double _y;
            };
        }
    }
}
