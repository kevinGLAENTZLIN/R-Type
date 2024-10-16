/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Score
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace Player
        {
            class Score: public ACommand{
                public:
                    Score() = default;
                    ~Score();

                    void set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int score);
                    void set_client(udp::endpoint endpoint);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::map<int, std::shared_ptr<Rtype::client_info>> _players;
                    int _score;
            };
        }
    }
}
