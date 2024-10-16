/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
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
            class Die: public ACommand{
                public:
                    Die() = default;
                    ~Die();

                    void set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int mobID);
                    void set_client();

                    void execute_client_side();
                    void execute_server_side();
            
                protected:
                private:
                    std::map<int, std::shared_ptr<Rtype::client_info>> _players;
                    int _mobID;
            };
        }
    }
}
