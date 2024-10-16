/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game_result
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
            class Game_result: public ACommand{
                public:
                    Game_result() = default;
                    ~Game_result();

                    void set_client();
                    void set_server(udp::endpoint endpoint, std::shared_ptr<Rtype::Game_info> game);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                udp::endpoint _endpoint;
                std::shared_ptr<Rtype::Game_info> _game;
            };
        }
    }
}
