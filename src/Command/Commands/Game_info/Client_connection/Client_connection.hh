/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_connection
*/

#pragma once
#include "../../../ICommand.hh"
#include "../../../../Server/udp_server.hh"

namespace Rtype
{
    namespace Command
    {
        namespace GameInfo
        {
            class Client_connection: ICommand{
                public:
                    Client_connection(udp::endpoint endpoint);
                    Client_connection(udp::endpoint endpoint, std::map<int, Rtype::client_info> &clients);
                    ~Client_connection();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    int get_available_client_id();

                    udp::endpoint _endpoint;
                    std::map<int, Rtype::client_info> _clients;
            };
        }
    }
}
