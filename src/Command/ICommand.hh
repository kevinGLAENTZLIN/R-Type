/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ICommand
*/

#pragma once
#if defined(_WIN32)           
	#define NOGDI             // All GDI defines and routines
	#define NOUSER            // All USER defines and routines
#endif

<<<<<<< HEAD
#include "raylib-cpp.hpp"

#if defined(_WIN32)           // raylib uses these names as function parameters
	#undef near
	#undef far
#endif

=======
>>>>>>> d669fe12eeee9ddacaae29b8270b4933c164e2b4
#include "../Client/Game/Game.hh"
#include <boost/asio.hpp>

using boost::asio::ip::udp;

namespace Rtype
{
    namespace Command
    {
        class ICommand {
            public:
                virtual ~ICommand() {}
                virtual void execute_client_side() = 0;
                virtual void execute_server_side() = 0;
                virtual void setOrigins(std::string origins) = 0;
        };
    }
}
