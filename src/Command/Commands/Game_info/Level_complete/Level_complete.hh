/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Level_complete
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
            class Level_complete: ICommand{
                public:
                    Level_complete();
                    Level_complete(udp::endpoint endpoint, Rtype::Game_info &game);
                    ~Level_complete();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    Rtype::Game_info _game;
            };
        }
    }
}
