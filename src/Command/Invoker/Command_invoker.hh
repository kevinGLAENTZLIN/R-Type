/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command_invoker
*/

#pragma once
#if defined(_WIN32)
	#define NOGDI             // All GDI defines and routines
	#define NOUSER            // All USER defines and routines
#endif

#include "raylib-cpp.hpp"

#if defined(_WIN32)           // raylib uses these names as function parameters
	#undef near
	#undef far
#endif
#include <iostream>
#include <iostream>
#include <queue>
#include <string>
#include "../ACommand.hpp"

namespace Rtype
{
    namespace Command
    {
        /**
         * @brief Command_invoker is responsible for managing and executing queued commands.
         *
         * This class stores a queue of commands and executes them sequentially.
         * It allows commands to be added to the queue and executes each command in order.
         */
        class Command_invoker {
            public:
                /**
                * @brief Constructs a Command_invoker with a specified invoker type.
                *
                * Initializes the invoker with a specified type to identify the command invoker.
                *
                * @param invoker_type A string representing the type of the invoker.
                */
                Command_invoker(std::string invoker_type);

                /**
                * @brief Destructs the Command_invoker.
                */
                ~Command_invoker();

                /**
                * @brief Executes the next command in the queue.
                *
                * This method retrieves the next command from the queue and executes it.
                * If the queue is empty, no action is taken.
                */
                void executeCommand();

                /**
                * @brief Adds a command to the queue for later execution.
                *
                * This method enqueues a command, which will be executed in the order
                * it was added when `executeCommand` is called.
                *
                * @param cmd A unique pointer to an `ACommand` to be added to the queue.
                */
                void addCommand(std::unique_ptr<Rtype::Command::ACommand> cmd);

            protected:
            private:
                std::string _invokerType;
                std::queue<std::unique_ptr<Rtype::Command::ACommand>> _commandQueue;
        };
    }
}
