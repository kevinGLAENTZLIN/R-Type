/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Score
*/

#pragma once
#include "../../../ICommand.hh"
#include "../../../../Server/udp_server.hh"

namespace Rtype
{
    namespace Command
    {
        namespace Player
        {
            class Score: public ICommand{
                public:
                    Score() = default;
                    ~Score();

                    void set_server(std::map<int, Rtype::client_info> players, int score);
                    void set_client(udp::endpoint endpoint);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::map<int, Rtype::client_info> _players;
                    int _score;
            };
        }
    }
}
