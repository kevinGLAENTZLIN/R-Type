/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command_invoker
*/

#pragma once
#include <iostream> 
#include <stack>
#include <string>
#include "../ICommand.hh"

namespace Rtype
{
    namespace Command
    {
        class Command_invoker {
            public:
                Command_invoker(std::string invoker_type);
                ~Command_invoker();

                void executeCommand();

                void addCommand(std::shared_ptr<ICommand> cmd);

            protected:
            private:
                std::string _invokerType;
                std::stack<std::shared_ptr<ICommand>> _commandStack;
        };
    }
}