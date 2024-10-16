/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hit_wall
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
            class Hit_wall: public ACommand{
                public:
                    Hit_wall() = default;
                    ~Hit_wall();

                    void set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int playerID);
                    void set_client(udp::endpoint endpoint);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::map<int, std::shared_ptr<Rtype::client_info>> _players;
                    int _playerID;
            };
        }
    }
}
