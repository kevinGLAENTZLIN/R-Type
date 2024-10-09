/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
*/

#pragma once
#include "../../../ICommand.hh"
#include "../../../../Server/udp_server.hh"

namespace Rtype
{
    namespace Command
    {
        namespace Boss
        {
            class Die: ICommand{
                public:
                    Die(std::map<int, Rtype::client_info> players, int bossType);
                    Die();
                    ~Die();

                    void execute_client_side();
                    void execute_server_side();
            
                protected:
                private:
                    std::map<int, Rtype::client_info> _players;
                    int _bossType;
            };
        }
    }
}
