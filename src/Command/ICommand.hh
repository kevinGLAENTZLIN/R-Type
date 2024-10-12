/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ICommand
*/

#pragma once

namespace Rtype
{
    namespace Command
    {
        class ICommand {
            public:
                virtual ~ICommand() {}
                virtual void execute_client_side();
                virtual void execute_server_side();

                virtual void set_server();
                virtual void set_client();
        };
    }
}