/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Join_game
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
            class Join_game: ICommand{
                public:
                    Join_game(udp::endpoint endpoint, int gameRoom);
                    Join_game(udp::endpoint endpoint, Rtype::Game_info &game);
                    ~Join_game();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    int _gameRoom;
                    Rtype::Game_info _game;
            };
        }
    }
}
