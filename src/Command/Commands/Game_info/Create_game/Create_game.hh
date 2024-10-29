/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Create_game
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
#include "../../../../Server/Game_info.hh"

namespace Rtype
{
    namespace Command
    {
        namespace GameInfo
        {
            class Create_game: public ACommand{
                public:
                    Create_game() = default;
                    ~Create_game();

                    void set_client();
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::Game_info>>> games);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    int getRoomIdAvailable(bool set_seed) const;

                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::Game_info>>> _games;
            };
        }
    }
}
