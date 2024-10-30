/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Level_complete
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
            class Level_complete: public ACommand {
                public:
                    Level_complete() = default;
                    ~Level_complete();

                    void set_client();
                    void set_server(std::shared_ptr<Rtype::Game_info> game);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    std::shared_ptr<Rtype::Game_info> _gameInfo;
            };
        }
    }
}
