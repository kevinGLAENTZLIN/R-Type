/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Level_complete
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Game_info.hh"

namespace Rtype
{
    namespace Command
    {
        namespace GameInfo
        {
            class Level_complete: public ACommand{
                public:
                    Level_complete() = default;
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
