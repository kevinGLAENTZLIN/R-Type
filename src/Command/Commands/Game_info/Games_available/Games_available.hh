/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Games_available
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
            class Games_available: public ICommand{
                public:
                    Games_available() = default;
                    ~Games_available();

                    void set_client(udp::endpoint endpoint);
                    void set_server(udp::endpoint endpoint, std::vector<Rtype::Game_info> games);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::vector<Rtype::Game_info> _games;
            };
        }
    }
}
