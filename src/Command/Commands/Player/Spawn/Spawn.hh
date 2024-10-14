/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
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
            class Spawn: public ICommand{
                public:
                    Spawn() = default;
                    ~Spawn();

                    void set_server(std::map<int, Rtype::client_info> players, int playerID, int x, int y);
                    void set_client();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    std::map<int, Rtype::client_info> _players;
                    int _playerID;
                    int _x;
                    int _y;
            };
        }
    }
}
