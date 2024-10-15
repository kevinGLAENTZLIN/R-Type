/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Attack
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
            class Attack: public ACommand{
                public:
                    Attack() = default;
                    ~Attack();

                    void set_server(std::map<int, Rtype::client_info> players, int projectileID);
                    void set_client(udp::endpoint endpoint, int projectileID);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::map<int, Rtype::client_info> _players;
                    int _projectileID;
            };
        }
    }
}
