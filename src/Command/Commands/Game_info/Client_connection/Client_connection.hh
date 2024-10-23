/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_connection
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Game_info.hh"
#include <map>

namespace Rtype
{
    namespace Command
    {
        namespace GameInfo
        {
            class Client_connection : public ACommand{
                public:
                    Client_connection() = default;
                    ~Client_connection();

                    void set_client();
                    void set_server(std::map<int, std::shared_ptr<Rtype::client_info>> &clients);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    int get_available_client_id();

                    std::map<int, std::shared_ptr<Rtype::client_info>> _clients;
            };
        }
    }
}
