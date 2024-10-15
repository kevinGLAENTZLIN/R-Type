/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Create_game
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
            class Create_game: public ACommand{
                public:
                    Create_game() = default;
                    ~Create_game();

                    void set_client(udp::endpoint endpoint);
                    void set_server(udp::endpoint endpoint, std::vector<std::shared_ptr<Rtype::Game_info>> &games);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::vector<std::shared_ptr<Rtype::Game_info>> _games;
            };
        }
    }
}
