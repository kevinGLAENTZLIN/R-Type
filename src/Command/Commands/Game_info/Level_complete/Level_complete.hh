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
            class Level_complete: public ICommand{
                public:
                    Level_complete();
                    ~Level_complete();

                    void set_client();
                    void set_server(udp::endpoint endpoint, Rtype::Game_info &game);

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
