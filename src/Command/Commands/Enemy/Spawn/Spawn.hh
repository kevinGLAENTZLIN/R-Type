/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace Enemy
        {
            class Spawn: public ACommand{
                public:
                    Spawn() = default;
                    ~Spawn();

                    void set_server(std::map<int, Rtype::client_info> players, int mobType, int mobID, int x, int y);
                    void set_client();

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
