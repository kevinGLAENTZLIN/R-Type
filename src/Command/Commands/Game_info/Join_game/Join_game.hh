/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Join_game
*/

#pragma once
#include "../../../ICommand.hh"
#include "../../../../Server/Game_info.hh"

namespace Rtype
{
    namespace Command
    {
        namespace GameInfo
        {
            class Join_game: public ICommand{
                public:
                    Join_game() = default;
                    ~Join_game();

                    void set_client(udp::endpoint endpoint, int gameRoom);
                    void set_server(udp::endpoint endpoint, Rtype::Game_info &game);

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
