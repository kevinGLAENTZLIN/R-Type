/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Missing_packages.hh
*/

#pragma once
#include "../../../ACommand.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace GameInfo
        {
            class Missing_packages
            {
            public:
                Missing_packages() = default;
                ~Missing_packages();


                void set_client(uint32_t _ack0, uint32_t _ack1, uint32_t _ack2, uint32_t _ack3);
                void set_server();

                void execute_client_side();
                void execute_server_side();
            private:
                uint32_t _ack0;
                uint32_t _ack1;
                uint32_t _ack2;
                uint32_t _ack3;
            };
            

        } // namespace GameInfo
        
    } // namespace Command
}