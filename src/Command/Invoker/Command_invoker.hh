/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command_invoker
*/

#pragma once
#include <iostream> 
#include <queue>
#include <string>
#include "../ACommand.hpp"

namespace Rtype
{
    namespace Command
    {
        class Command_invoker {
            public:
                Command_invoker(std::string invoker_type);
                ~Command_invoker();

                void executeCommand();

                void addCommand(std::unique_ptr<ACommand> cmd);

            protected:
            private:
                std::string _invokerType;
                std::queue<std::unique_ptr<ACommand>> _commandQueue;
        };
    }
}