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

                    void set_client();
                    void set_server(std::shared_ptr<std::vector<std::shared_ptr<Rtype::Game_info>>> games);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    int getRoomIdAvailable(bool set_seed) const;

                    udp::endpoint _endpoint;
                    std::shared_ptr<std::vector<std::shared_ptr<Rtype::Game_info>>> _games;
            };
        }
    }
}
