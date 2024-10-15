/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hit
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace Projectile
        {
            class Hit: public ACommand{
                public:
                    Hit() = default;
                    ~Hit();

                    void set_server(std::map<int, Rtype::client_info> players, int projectileID);
                    void set_client();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    std::map<int, Rtype::client_info> _players;
                    int _projectileID;
            };
        }
    }
}
