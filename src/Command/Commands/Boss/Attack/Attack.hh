/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Attack
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
            class Attack: ICommand{
                public:
                    Attack(std::map<int, Rtype::client_info> players, int bossType, int bossAttackType);
                    Attack();
                    ~Attack();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    std::map<int, Rtype::client_info> _players;
                    int _bossType;
                    int _bossAttackType;
            };
        }
    }
}
