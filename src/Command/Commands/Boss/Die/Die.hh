/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
*/

#pragma once
#include "../../../ICommand.hh"
#include "../../../../Server/Client_info.hh"

namespace Rtype
{
    namespace Command
    {
        namespace Boss
        {
            class Die: public ICommand{
                public:
                    Die() = default;
                    ~Die();

                    void set_server(std::map<int, Rtype::client_info> players, int bossType);
                    void set_client();

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
