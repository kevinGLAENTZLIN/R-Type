/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Attack
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace Boss
        {
            class Attack: public ACommand{
                public:
                    Attack() = default;
                    ~Attack();

                    void set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int bossType, int bossAttackType);
                    void set_client();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    std::map<int, std::shared_ptr<Rtype::client_info>> _players;
                    int _bossType;
                    int _bossAttackType;
            };
        }
    }
}
