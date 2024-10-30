/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Level_complete
*/

#pragma once
#if defined(_WIN32)           
	#define NOGDI
	#define NOUSER
#endif

#if defined(_WIN32)
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
