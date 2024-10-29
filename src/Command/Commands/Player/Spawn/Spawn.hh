/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
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
#include "../../../ACommand.hpp"
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace Player
        {
            class Spawn: public ACommand{
                public:
                    Spawn() = default;
                    ~Spawn();

                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int playerID, double x, double y);
                    void set_client();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _playerID;
                    double _x;
                    double _y;
            };
        }
    }
}
