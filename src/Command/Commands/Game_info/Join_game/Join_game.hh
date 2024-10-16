/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Join_game
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Game_info.hh"
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace GameInfo
        {
            class Join_game: public ACommand{
                public:
                    Join_game() = default;
                    ~Join_game();

                    void set_client(udp::endpoint endpoint, int gameRoom);
                    void set_server(udp::endpoint endpoint, std::shared_ptr<Rtype::Game_info> game, std::shared_ptr<Rtype::client_info> client_info);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    int _gameRoom;
                    std::shared_ptr<Rtype::Game_info> _gameInfo;
                    std::shared_ptr<Rtype::client_info> _clientInfo;
            };
        }
    }
}
