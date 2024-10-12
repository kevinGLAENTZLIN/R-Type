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
        namespace Player
        {
            class Die: public ICommand{
                public:
                    Die();
                    ~Die();

                    void set_client();
                    void set_server(std::map<int, Rtype::client_info> players, int playerID);

                    void execute_client_side();
                    void execute_server_side();
            
                protected:
                private:
                    std::map<int, Rtype::client_info> _players;
                    int _playerID;
            };
        }
    }
}
