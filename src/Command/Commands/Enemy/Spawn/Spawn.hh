/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#pragma once
#include "../../../ICommand.hh"
#include "../../../../Server/udp_server.hh"

namespace Rtype
{
    namespace Command
    {
        namespace Enemy
        {
            class Spawn: ICommand{
                public:
                    Spawn(std::map<int, Rtype::client_info> players, int mobType, int mobID, int x, int y);
                    Spawn();
                    ~Spawn();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    std::map<int, Rtype::client_info> _players;
                    int _mobType;
                    int _mobID;
                    int _x;
                    int _y;
            };
        }
    }
}
