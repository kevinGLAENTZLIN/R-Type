/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Create_game
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
            class Create_game: ICommand{
                public:
                    Create_game(udp::endpoint endpoint);
                    Create_game(udp::endpoint endpoint, std::vector<int> &games);
                    ~Create_game();

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
