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
            class Games_available: ICommand{
                public:
                    Games_available(udp::endpoint endpoint);
                    Games_available(udp::endpoint endpoint, std::vector<Rtype::Game_info> games);
                    ~Games_available();

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
