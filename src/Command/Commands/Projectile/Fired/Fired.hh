/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Fired
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
        namespace Projectile
        {
            class Fired: public ACommand{
                public:
                    Fired() = default;
                    ~Fired();

                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int entityID, int projectileID);
                    void set_client();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _entityID;
                    int _projectileID;
            };
        }
    }
}
