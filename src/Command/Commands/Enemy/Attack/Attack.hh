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
        namespace Enemy
        {
            class Attack: public ICommand{
                public:
                    Attack() = default;
                    ~Attack();

                    void set_server(std::map<int, Rtype::client_info> players, int mobID);
                    void set_client();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    std::map<int, Rtype::client_info> _players;
                    int _mobID;
            };
        }
    }
}
